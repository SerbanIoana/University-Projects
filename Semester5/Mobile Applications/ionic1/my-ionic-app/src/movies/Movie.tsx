import React from 'react';
import { IonItem, IonLabel } from '@ionic/react';
import { MovieProps } from './MovieProps';

interface MoviePropsExt extends MovieProps {
  onEdit: (id?: string) => void;
}

const Movie: React.FC<MoviePropsExt> = ({ id, title, budget, premiere, isOnTV, onEdit }) => {
  return (
    <IonItem onClick={() => onEdit(id)}>
        <IonLabel>{title}</IonLabel>
        <IonLabel>budget: {budget}$</IonLabel>
        <IonLabel>premiere date: {premiere}</IonLabel>
        <IonLabel>aired on TV: {isOnTV}</IonLabel>
    </IonItem>
  );
};

export default Movie;
