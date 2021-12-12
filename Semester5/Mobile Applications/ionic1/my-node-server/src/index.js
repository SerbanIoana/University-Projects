const Koa = require('koa');
const app = new Koa();
const server = require('http').createServer(app.callback());
const WebSocket = require('ws');
const wss = new WebSocket.Server({server});
const Router = require('koa-router');
const cors = require('koa-cors');
const bodyparser = require('koa-bodyparser');

app.use(bodyparser());
app.use(cors());
app.use(async (ctx, next) => {
    const start = new Date();
    await next();
    const ms = new Date() - start;
    console.log(`${ctx.method} ${ctx.url} ${ctx.response.status} - ${ms}ms`);
});

app.use(async (ctx, next) => {
    await new Promise(resolve => setTimeout(resolve, 2000));
    await next();
});

app.use(async (ctx, next) => {
    try {
        await next();
    } catch (err) {
        ctx.response.body = {issue: [{error: err.message || 'Unexpected error'}]};
        ctx.response.status = 500;
    }
});

class Movie {
    constructor({id, title, budget, premiere, isOnTV, date, version}) {
        this.id = id;
        this.title = title;
        this.budget = budget;
        this.premiere = premiere;
        this.isOnTV = isOnTV;
        this.date = date;
        this.version = version;
    }
}

const movies = [];
const dateStart = new Date(1900, 0).getTime();
const dateEnd = new Date().getTime();
for (let i = 0; i < 3; i++) {
    const datePremiere = new Date(dateStart + Math.random() * (dateEnd - dateStart));
    const budgetRandom = Math.floor(Math.random() * 10000) + 3000;
    movies.push(new Movie({
        id: `${i}`,
        title: `movie ${i}`,
        budget: budgetRandom,
        premiere: datePremiere.toISOString().substring(0, 10),
        isOnTV: false.toString(),
        date: new Date(Date.now() + i),
        version: 1
    }));
}

let lastUpdated = movies[movies.length - 1].date;
let lastId = movies[movies.length - 1].id;
const pageSize = 10;

const broadcast = data =>
    wss.clients.forEach(client => {
        if (client.readyState === WebSocket.OPEN) {
            client.send(JSON.stringify(data));
        }
    });

const router = new Router();

router.get('/movie', ctx => {
    const ifModifiedSince = ctx.request.get('If-Modified-Since');
    if (ifModifiedSince && new Date(ifModifiedSince).getTime() >= lastUpdated.getTime() - lastUpdated.getMilliseconds()) {
        ctx.response.status = 304; // NOT MODIFIED
        return;
    }
    const title = ctx.request.query.title;
    const page = parseInt(ctx.request.query.page) || 1;
    ctx.response.set('Last-Modified', lastUpdated.toUTCString());
    const sortedMovies = movies
        .filter(movie => title ? movie.title.indexOf(title) !== -1 : true)
        .sort((n1, n2) => -(n1.date.getTime() - n2.date.getTime()));
    const offset = (page - 1) * pageSize;
    // ctx.response.body = {
    //   page,
    //   movies: sortedMovies.slice(offset, offset + pageSize),
    //   more: offset + pageSize < sortedMovies.length
    // };
    ctx.response.body = movies;
    ctx.response.status = 200;
});

router.get('/movie/:id', async (ctx) => {
    const movieId = ctx.request.params.id;
    const movie = movies.find(movie => movieId === movie.id);
    if (movie) {
        ctx.response.body = movie;
        ctx.response.status = 200; // ok
    } else {
        ctx.response.body = {issue: [{warning: `movie with id ${movieId} not found`}]};
        ctx.response.status = 404; // NOT FOUND (if you know the resource was deleted, then return 410 GONE)
    }
});

const createMovie = async (ctx) => {
    const movie = ctx.request.body;
    if (!movie.title) { // validation
        ctx.response.body = {issue: [{error: 'Title is missing'}]};
        ctx.response.status = 400; //  BAD REQUEST
        return;
    }
    if (!movie.budget) {
        ctx.response.body = {issue: [{error: 'Budget is missing'}]};
        ctx.response.status = 400; //  BAD REQUEST
        return;
    }
    if (!movie.premiere) {
        ctx.response.body = {issue: [{error: 'Premiere date is missing'}]};
        ctx.response.status = 400; //  BAD REQUEST
        return;
    }
    if (!movie.isOnTV) {
        ctx.response.body = {issue: [{error: 'IsOnTV for movie is missing'}]};
        ctx.response.status = 400; //  BAD REQUEST
        return;
    }
    movie.id = `${parseInt(lastId) + 1}`;
    lastId = movie.id;
    movie.date = new Date();
    movie.version = 1;
    movies.push(movie);
    ctx.response.body = movie;
    ctx.response.status = 201; // CREATED
    broadcast({event: 'created', payload: {movie}});
};

router.post('/movie', async (ctx) => {
    await createMovie(ctx);
});

router.put('/movie/:id', async (ctx) => {
    const id = ctx.params.id;
    const movie = ctx.request.body;
    movie.date = new Date();
    const movieId = movie.id;
    if (movieId && id !== movie.id) {
        ctx.response.body = {issue: [{error: `Param id and body id should be the same`}]};
        ctx.response.status = 400; // BAD REQUEST
        return;
    }
    if (!movieId) {
        await createMovie(ctx);
        return;
    }
    const index = movies.findIndex(movie => movie.id === id);
    if (index === -1) {
        ctx.response.body = {issue: [{error: `movie with id ${id} not found`}]};
        ctx.response.status = 400; // BAD REQUEST
        return;
    }
    const movieVersion = parseInt(ctx.request.get('ETag')) || movie.version;
    if (movieVersion < movies[index].version) {
        ctx.response.body = {issue: [{error: `Version conflict`}]};
        ctx.response.status = 409; // CONFLICT
        return;
    }
    movie.version++;
    movies[index] = movie;
    lastUpdated = new Date();
    ctx.response.body = movie;
    ctx.response.status = 200; // OK
    broadcast({event: 'updated', payload: {movie}});
});

router.del('/movie/:id', ctx => {
    const id = ctx.params.id;
    const index = movies.findIndex(movie => id === movie.id);
    if (index !== -1) {
        const movie = movies[index];
        movies.splice(index, 1);
        lastUpdated = new Date();
        broadcast({event: 'deleted', payload: {movie}});
    }
    ctx.response.status = 204; // no content
});

setInterval(() => {
    lastUpdated = new Date();
    lastId = `${parseInt(lastId) + 1}`;
    const datePremiere = new Date(dateStart + Math.random() * (dateEnd - dateStart));
    const budgetRandom = Math.floor(Math.random() * 10000) + 3000;
    const movie = new Movie({
        id: lastId,
        title: `movie ${lastId}`,
        budget: budgetRandom,
        premiere: datePremiere.toISOString().substring(0, 10),
        isOnTV: false.toString(),
        date: lastUpdated,
        version: 1
    });
    movies.push(movie);
    console.log(`${movie.title}`);
    broadcast({event: 'created', payload: {movie}});
}, 150000);

app.use(router.routes());
app.use(router.allowedMethods());

server.listen(3000);
