import React, {useContext, useEffect, useState} from 'react';
import {
    IonButton,
    IonButtons,
    IonContent, IonDatetime,
    IonHeader,
    IonInput,
    IonLoading,
    IonPage,
    IonTitle,
    IonToolbar,
    IonCheckbox, IonLabel, IonItem
} from '@ionic/react';
import {getLogger} from '../core';
import {MovieContext} from './MovieProvider';
import {RouteComponentProps} from 'react-router';
import {MovieProps} from './MovieProps';

const log = getLogger('MovieEdit');

interface MovieEditProps extends RouteComponentProps<{
    id?: string;
}> {
}

const MovieEdit: React.FC<MovieEditProps> = ({history, match}) => {
    const {movies, saving, savingError, saveMovie} = useContext(MovieContext);
    const [title, setTitle] = useState('');
    const [budget, setBudget] = useState(0);
    const [premiere, setPremiere] = useState(new Date());
    const [isOnTV, setIsOnTV] = useState(false);
    const [movie, setMovie] = useState<MovieProps>();

    useEffect(() => {
        log('useEffect');
        const routeId = match.params.id || '';
        const movie = movies?.find(it => it._id === routeId);
        setMovie(movie);
        if (movie) {
            setTitle(movie.title);
            setBudget(movie.budget);
            setPremiere(movie.premiere);
            setIsOnTV(movie.isOnTV);
        }
    }, [match.params.id, movies]);
    const handleSave = () => {
        const editedMovie = movie ? {...movie, title, budget, premiere, isOnTV} : {title, budget, premiere, isOnTV};
        saveMovie && saveMovie(editedMovie).then(() => history.goBack());
    };
    log('render');
    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>Edit</IonTitle>
                    <IonButtons slot="end">
                        <IonButton onClick={handleSave}>
                            Save
                        </IonButton>
                    </IonButtons>
                </IonToolbar>
            </IonHeader>
            <IonContent>
                <IonItem>
                    <IonLabel position="floating">Title</IonLabel>
                    <IonInput value={title} onIonChange={e => setTitle(e.detail.value || '')}/>
                </IonItem>

                <IonItem>
                    <IonLabel position="floating">Budget $</IonLabel>
                    <IonInput value={budget} onIonChange={e => setBudget(Number(e.detail.value) || 0)}/>
                </IonItem>

                <IonItem>
                    <IonLabel position="floating">Premiere date</IonLabel>
                    <IonDatetime displayFormat="DD MM YYYY" placeholder="Select Date"
                                 value={new Date(premiere).toISOString().substring(0, 10)}
                                 onIonChange={e => setPremiere(new Date(e.detail.value || 0))}/>
                </IonItem>

                <IonItem>
                    <IonLabel position="floating">Aired on TV</IonLabel>
                    <IonCheckbox checked={isOnTV} onIonChange={e => setIsOnTV(e.detail.checked)}/>
                </IonItem>

                <IonLoading isOpen={saving}/>
                {savingError && (
                    <div>{savingError.message || 'Failed to save movie'}</div>
                )}
            </IonContent>
        </IonPage>
    );
};

export default MovieEdit;
