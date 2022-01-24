import axios from 'axios';
import {authConfig, baseUrl, getLogger, withLogs} from '../core';
import {MovieProps} from './MovieProps';

const movieUrl = `http://${baseUrl}/api/movie`;

export const getMovies: (token: string, offset?: number, pageSize?: number) => Promise<MovieProps[]> = (token, offset, pageSize) => {
    if (offset !== undefined && pageSize !== undefined)
        return withLogs(axios.get(movieUrl, {...authConfig(token), params: {offset, pageSize}}),'getMoviesPaginated');
    else
        return withLogs(axios.get(movieUrl, authConfig(token)), 'getMovies');
}

export const createMovie: (token: string, movie: MovieProps) => Promise<MovieProps[]> = (token, movie) => {
    return withLogs(axios.post(movieUrl, movie, authConfig(token)), 'createMovie');
}

export const updateMovie: (token: string, movie: MovieProps) => Promise<MovieProps[]> = (token, movie) => {
    return withLogs(axios.put(movieUrl, movie, authConfig(token)), 'updateMovie');
}

export const syncMovies: (token: string, movies: MovieProps[]) => Promise<any> = (token, movies) => {
    return withLogs(axios.put(`${movieUrl}/sync`, movies, authConfig(token)), 'syncMovies');
}

interface MessageData {
    type: string;
    payload: {
        movie: MovieProps;
    };
}

const log = getLogger('ws');

export const newWebSocket = (token: string, onMessage: (data: MessageData) => void) => {
    const ws = new WebSocket(`ws://${baseUrl}`);
    ws.onopen = () => {
        log('web socket onopen');
        ws.send(JSON.stringify({ type: 'authorization', payload: { token } }));
    };
    ws.onclose = () => {
        log('web socket onclose');
    };
    ws.onerror = error => {
        log('web socket onerror', error);
    };
    ws.onmessage = messageEvent => {
        log('web socket onmessage');
        onMessage(JSON.parse(messageEvent.data));
    };
    return () => {
        ws.close();
    }
}