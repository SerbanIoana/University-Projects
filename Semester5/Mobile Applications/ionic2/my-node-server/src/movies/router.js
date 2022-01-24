import Router from 'koa-router';
import movieStore from './store';
import { broadcast } from "../utils";

export const router = new Router();

let paginationCount = 0;
const paginationNbr = 10;



// router.get('/', async (ctx) => { //ctx = {request, response, state} state is used by jwt to check if the user is auth
//     const response = ctx.response;
//     const userId = ctx.state.user._id;
//     response.body = await getMoviesPaginated(userId);
//     response.status = 200; //ok
// });


router.get('/', async (ctx) => {
  const {offset, pagSize} = ctx.query;
  const response = ctx.response;
  const userId = ctx.state.user._id;
  if (offset && pagSize) {
    response.body = await movieStore.getMoviesPaginated(offset, pagSize, {userId});
  }
  else
    response.body = await movieStore.find({ userId });
  response.status = 200; // ok
});

router.get('/:id', async (ctx) => {
  const userId = ctx.state.user._id;
  const movie = await movieStore.findOne({ _id: ctx.params.id });
  const response = ctx.response;
  if (movie) {
    if (movie.userId === userId) {
      response.body = movie;
      response.status = 200; // ok
    } else {
      response.status = 403; // forbidden
    }
  } else {
    response.status = 404; // not found
  }
});

const createMovie = async (ctx, movie, response) => {
  try {
    const userId = ctx.state.user._id;
    movie.userId = userId;
    response.body = await movieStore.insert(movie);
    console.log(response.body);
    response.status = 201; // created
    broadcast(userId, { type: 'created', payload: {movie} });
    console.log('passed broadcast')
  } catch (err) {
    response.body = { message: err.message };
    response.status = 400; // bad request
  }
};

router.post('/', async ctx => await createMovie(ctx, ctx.request.body, ctx.response));

router.put('/', async (ctx) => {
  const movie = ctx.request.body;
  const movieId = movie._id;
  const response = ctx.response;
  console.log(ctx.request.body);

  if (!movieId) {
    console.log("make new movie")
    await createMovie(ctx, movie, response);
  } else {
    console.log("found movie")
    const userId = ctx.state.user._id;
    movie.userId = userId;
    const updatedCount = await movieStore.update({ _id: movieId }, movie);
    if (updatedCount === 1) {
      response.body = movie;
      console.log(response.body)
      response.status = 200; // ok
      broadcast(userId, { type: 'updated', payload: {movie} });
    } else {
      response.body = { message: 'Resource no longer exists' };
      response.status = 405; // method not allowed
    }
  }
});

router.del('/:id', async (ctx) => {
  console.log("delete")
  console.log(ctx.state.user)

  const userId = ctx.state.user._id;
  const movie = await movieStore.findOne({ _id: ctx.params.id });

  console.log(userId)
  console.log(movie)
  if (movie && userId !== movie.userId) {
    ctx.response.status = 403; // forbidden
  } else {
    await movieStore.remove({ _id: ctx.params.id });
    ctx.response.status = 204; // no content
  }
});

router.put('/sync', async (ctx) => {
  const movies = ctx.request.body;
  for (let i=0; i<movies.length; i++) {
    const movie = movies[i];
    if (await movieStore.findOne({_id: movie._id}))
      await movieStore.update({ _id: movie._id }, movie);
    else await movieStore.insert(movie);
  }
  ctx.response.status = 200;
});