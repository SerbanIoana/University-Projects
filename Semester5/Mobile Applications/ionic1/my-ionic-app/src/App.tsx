import React from 'react';
import { Redirect, Route } from 'react-router-dom';
import { IonApp, IonRouterOutlet } from '@ionic/react';
import { IonReactRouter } from '@ionic/react-router';
import { MovieEdit, MovieList } from './movies';

/* Core CSS required for Ionic components to work properly */
import '@ionic/react/css/core.css';

/* Basic CSS for apps built with Ionic */
import '@ionic/react/css/normalize.css';
import '@ionic/react/css/structure.css';
import '@ionic/react/css/typography.css';

/* Optional CSS utils that can be commented out */
import '@ionic/react/css/padding.css';
import '@ionic/react/css/float-elements.css';
import '@ionic/react/css/text-alignment.css';
import '@ionic/react/css/text-transformation.css';
import '@ionic/react/css/flex-utils.css';
import '@ionic/react/css/display.css';

/* Theme variables */
import './theme/variables.css';
import {MovieProvider} from "./movies/MovieProvider";

const App: React.FC = () => (
  <IonApp>
    <MovieProvider>
      <IonReactRouter>
        <IonRouterOutlet>
          {/*<Route path="/items" component={ItemList} exact={true} />*/}
          {/*<Route path="/item" component={ItemEdit} exact={true} />*/}
          {/*<Route path="/item/:id" component={ItemEdit} exact={true} />*/}
          {/*<Route exact path="/" render={() => <Redirect to="/items" />} />*/}
          <Route path="/movies" component={MovieList} exact={true} />
          <Route path="/movie" component={MovieEdit} exact={true} />
          <Route path="/movie/:id" component={MovieEdit} exact={true} />
          <Route exact path="/" render={() => <Redirect to="/movies"/>} />
        </IonRouterOutlet>
      </IonReactRouter>
    </MovieProvider>
  </IonApp>
);

export default App;