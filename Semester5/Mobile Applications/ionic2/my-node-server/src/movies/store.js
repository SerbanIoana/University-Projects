import dataStore from 'nedb-promise';

export class MovieStore {
  constructor({ filename, autoload }) {
    this.store = dataStore({ filename, autoload });
  }
  
  async find(props) {
    return this.store.find(props);
  }

  async getMoviesPaginated(offset, pagSize, props) {
    return this.store.find(props).slice(offset, offset + pagSize);
  }

  async findOne(props) {
    return this.store.findOne(props);
  }
  
  async insert(movie) {
    let movieTitle = movie.title;
    let movieBudget = movie.budget;
    let moviePremiere = movie.premiere;
    let movieIsOnTv = movie.isOnTV;

    if (!movieTitle) { // validation
      throw new Error('Missing title property')
    }
    if (!movieBudget) { // validation
      throw new Error('Missing budget property')
    }
    if (!moviePremiere) { // validation
      throw new Error('Missing premiere property')
    }
    if (!movieIsOnTv) { // validation
      throw new Error('Missing isOnTV property')
    }
    return this.store.insert(movie);
  };

  async insertAll(movies) {
    return this.store.insert(movies);
  }
  
  async update(props, note) {
    return this.store.update(props, note);
  }
  
  async remove(props) {
    return this.store.remove(props);
  }
}

export default new MovieStore({ filename: './db/movies.json', autoload: true });