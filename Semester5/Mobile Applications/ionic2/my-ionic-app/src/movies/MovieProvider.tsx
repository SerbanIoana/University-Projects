import React, {useCallback, useContext, useEffect, useReducer} from 'react';
import PropTypes from 'prop-types';
import {getLogger} from '../core';
import {MovieProps} from './MovieProps';
import {createMovie, getMovies, newWebSocket, syncMovies, updateMovie} from './movieApi';
import {AuthContext} from "../auth";
import {Storage} from '@capacitor/storage';
import {useNetwork} from "../core/useNetwork";

const log = getLogger('MovieProvider');

type SaveMovieFn = (movie: MovieProps) => Promise<any>;
type LoadNextMoviesFn = () => Promise<any>;


export interface MovieState {
    movies: MovieProps[],
    fetching: boolean,
    fetchingError?: Error | null,
    saving: boolean,
    savingError?: Error | null,
    saveMovie?: SaveMovieFn,
    loadNextMovies?: LoadNextMoviesFn,
    networkStatus?: any,
    loadedAll: boolean,
    currentOffset: number,
    pageSize: number
}

interface ActionProps {
    type: string,
    payload?: any,
}

const initialState = {
    movies: [],
    fetching: false,
    saving: false,
    currentOffset: 0,
    pageSize: 5,
    loadedAll: false
};

const FETCH_MOVIES_STARTED = 'FETCH_MOVIES_STARTED';
const FETCH_MOVIES_SUCCEEDED = 'FETCH_MOVIES_SUCCEEDED';
const FETCH_MOVIES_FAILED = 'FETCH_MOVIES_FAILED';
const SAVE_MOVIE_STARTED = 'SAVE_MOVIE_STARTED';
const SAVE_MOVIE_SUCCEEDED = 'SAVE_MOVIE_SUCCEEDED';
const SAVE_MOVIE_FAILED = 'SAVE_MOVIE_FAILED';
const GET_NEXT_MOVIES = 'GET_NEXT_MOVIES';

const reducer: (state: MovieState, action: ActionProps) => MovieState =
    (state, {type, payload}) => {
        switch (type) {
            case FETCH_MOVIES_STARTED:
                return {...state, fetching: true, fetchingError: null};
            case FETCH_MOVIES_SUCCEEDED:
                return {...state, movies: payload.movies, fetching: false};
            case FETCH_MOVIES_FAILED:
                return {...state, fetchingError: payload.error, fetching: false};
            case SAVE_MOVIE_STARTED:
                return {...state, savingError: null, saving: true};
            case SAVE_MOVIE_SUCCEEDED:
                const movies = [...(state.movies || [])];
                const movie = payload.movie;
                const index = movies.findIndex(it => it._id === movie._id);
                if (index === -1) {
                    movies.splice(0, 0, movie);
                } else {
                    movies[index] = movie;
                }
                return {...state, movies: movies, saving: false};
            case SAVE_MOVIE_FAILED:
                // console.log('SAVING ERROR: ' + payload.error);
                return {...state, savingError: payload.error, saving: false};
            case GET_NEXT_MOVIES:
                const stateMovies = [...(state.movies || [])];
                const newMovies = [...stateMovies, ...payload.movies];
                const newOffset = state.currentOffset + state.pageSize;
                return {
                    ...state,
                    fetching: false,
                    movies: newMovies,
                    currentOffset: newOffset,
                    loadedAll: payload.movies.length < state.pageSize
                };
            default:
                return state;
        }
    };

export const MovieContext = React.createContext<MovieState>(initialState);

interface MovieProviderProps {
    children: PropTypes.ReactNodeLike,
}

export const MovieProvider: React.FC<MovieProviderProps> = ({children}) => {
    const {token} = useContext(AuthContext);
    const [state, dispatch] = useReducer(reducer, initialState);
    const {movies, fetching, fetchingError, saving, savingError, currentOffset, loadedAll, pageSize} = state;
    const {networkStatus} = useNetwork();

    //useEffect(getMoviesEffect, [token]);
    useEffect(wsEffect, [token]);
    useEffect(() => {
        if (networkStatus.connected && movies && movies.length > 0) {
            syncMovies(token, movies);
        } else if (!networkStatus.connected && movies && movies.length > 0) {
            Storage.set({key: 'saveData', value: JSON.stringify(movies)});
        }
    }, [networkStatus]);

    const saveMovie = useCallback<SaveMovieFn>(saveMovieCallback, [token, networkStatus]);
    const loadNextMovies = useCallback<LoadNextMoviesFn>(loadNextMoviesCallback, [currentOffset, pageSize, token]);
    const value = {movies, fetching, fetchingError, saving, savingError, saveMovie, loadNextMovies, networkStatus, loadedAll, currentOffset, pageSize, token};
    log('returns');
    // networkStatusChanged();

    return (
        <MovieContext.Provider value={value}>
            {children}
        </MovieContext.Provider>
    );

    function getMoviesEffect() {
        let canceled = false;
        fetchMovies();
        return () => {
            canceled = true;
        }

        async function fetchMovies() {
            if (!token?.trim()) {
                return;
            }
            try {
                log('fetchMovies started');
                dispatch({type: FETCH_MOVIES_STARTED});
                const movies = await getMovies(token);
                log('fetchMovies succeeded');
                if (!canceled) {
                    dispatch({type: FETCH_MOVIES_SUCCEEDED, payload: {movies}});
                }
            } catch (error) {
                log('fetchMovies failed');
                dispatch({type: FETCH_MOVIES_FAILED, payload: {error}});
            }
        }
    }

    async function loadNextMoviesCallback() {
        if (!token?.trim()) {
            return;
        }
        else {
            try {
                dispatch({type: FETCH_MOVIES_STARTED});
                console.log(`Fetching movies: offset ${currentOffset} pageSize ${pageSize}`);
                const movies = await getMovies(token, currentOffset, pageSize);
                dispatch({type: GET_NEXT_MOVIES, payload: {movies}});
            } catch (error) {
                dispatch({type: FETCH_MOVIES_FAILED, payload: {error}});
            }
        }
    }


    async function saveMovieCallback(movie: MovieProps) {
        if (!networkStatus.connected) {
            let error = 'saveMovie failed because network is offline';
            log(error);
            let data;
            let res = await Storage.get({key: 'saveData'});
            data = JSON.parse(res.value ?? "[]");
            if (!movie._id)
                Storage.set({key: 'saveData', value: JSON.stringify([...data, movie])})
            else {
                const index = data.findIndex((m: MovieProps) => m._id === movie._id);
                data[index] = movie;
                Storage.set({key: 'saveData', value: JSON.stringify(data)});
            }

            dispatch({type: SAVE_MOVIE_SUCCEEDED, payload: {movie}});
        } else {
            try {
                log('saveMovie started');
                dispatch({type: SAVE_MOVIE_STARTED});
                const savedMovie = await (movie._id ? updateMovie(token, movie) : createMovie(token, movie));
                log('saveMovie succeeded');
                dispatch({type: SAVE_MOVIE_SUCCEEDED, payload: {movie: savedMovie}});
            } catch (error) {
                log('saveMovie failed');
                dispatch({type: SAVE_MOVIE_FAILED, payload: {error}});
                // dispatch({type: SAVE_MOVIE_FAILED, payload: {error}});

            }
        }
    }

    function networkStatusChanged() {
        let canceled = false;
        checkForUnsavedData();
        return () => {
            canceled = true;
        }

        async function checkForUnsavedData() {
            if (canceled) {
                return;
            }
            log(networkStatus.connected);
            if (networkStatus.connected) {
                let data = await Storage.get({key: 'saveData'});
                if (data.value) {
                    log(data);
                    let arrData = JSON.parse(data.value);
                    log(arrData);
                    if (arrData.length === 0) {
                        Storage.remove({key: 'saveData'});
                    } else {
                        let movie = arrData.pop();
                        try {
                            log('saveMovie started');
                            dispatch({type: SAVE_MOVIE_STARTED});
                            const savedMovie = await (movie._id ? updateMovie(token, movie) : createMovie(token, movie));
                            await Storage.set({key: 'saveData', value: JSON.stringify(arrData)})
                            dispatch({type: SAVE_MOVIE_SUCCEEDED, payload: {movie: savedMovie}});
                            log('saveMovie succeeded');
                        } catch (error) {
                            log('saveMovie failed');
                            arrData.push(movie);
                            dispatch({type: SAVE_MOVIE_FAILED, payload: {error, data: data}});
                        }
                    }
                }
            }
        }
    }

    function wsEffect() {
        let canceled = false;
        log('wsEffect - connecting');
        let closeWebSocket: () => void;
        if (token?.trim()) {
            closeWebSocket = newWebSocket(token, message => {
                if (canceled) {
                    return;
                }
                const {type, payload: {movie}} = message;
                log(`ws message, movie ${type}`);
                if (type === 'created' || type === 'updated') {
                    console.log(JSON.stringify(movie));
                    dispatch({type: SAVE_MOVIE_SUCCEEDED, payload: {movie}});
                }
            });
        }
        return () => {
            log('wsEffect - disconnecting');
            canceled = true;
            closeWebSocket?.();
        }
    }
};
