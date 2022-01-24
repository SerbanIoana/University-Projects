import React, {useContext, useEffect} from 'react';
import {RouteComponentProps} from 'react-router';
import {
    IonApp,
    IonContent,
    IonFab,
    IonFabButton,
    IonHeader,
    IonIcon, IonInfiniteScroll, IonInfiniteScrollContent,
    IonList, IonLoading,
    IonPage,
    IonTitle,
    IonToolbar
} from '@ionic/react';
import {add} from 'ionicons/icons';
import Movie from './Movie';
import {getLogger} from '../core';
import {MovieContext} from './MovieProvider';
import Logout from "../auth/Logout";
import {AuthProvider} from "../auth";
import MyNetwork from "../network/MyNetwork";

const log = getLogger('MovieList');

const MovieList: React.FC<RouteComponentProps> = ({history}) => {
    const {movies, fetching, fetchingError, loadNextMovies, loadedAll} = useContext(MovieContext);
    useEffect(() => {
        loadNextMovies && loadNextMovies();
    }, []);

    async function searchNext($event: CustomEvent<void>) {
        loadNextMovies && await loadNextMovies();
        await ($event.target as HTMLIonInfiniteScrollElement).complete();
    }

    log('render');
    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>Movie List</IonTitle>
                </IonToolbar>
            </IonHeader>

            <MyNetwork />

            <IonContent>
                <IonLoading isOpen={fetching} message="Fetching movies"/>
                {movies && (
                    <IonList>
                        {movies.map(({_id, title, budget, premiere, isOnTV}) =>
                            <Movie key={_id} _id={_id} title={title} budget={budget} premiere={premiere} isOnTV={isOnTV}
                                   onEdit={id => history.push(`/movie/${id}`)}/>)}
                    </IonList>
                )}
                {fetchingError && (
                    <div>{fetchingError.message || 'Failed to fetch movies'}</div>
                )}

                <IonInfiniteScroll threshold="100px" disabled={loadedAll} onIonInfinite={searchNext}>
                    <IonInfiniteScrollContent loadingText="Loading more movies"/>
                </IonInfiniteScroll>

                <IonFab vertical="bottom" horizontal="end" slot="fixed">
                    <IonFabButton onClick={() => history.push('/movie')}>
                        <IonIcon icon={add}/>
                    </IonFabButton>
                </IonFab>

                <IonFab vertical="bottom" horizontal="start" slot="fixed" z-index={9999}>
                    <Logout />
                </IonFab>

            </IonContent>
        </IonPage>
    );
};

export default MovieList;
