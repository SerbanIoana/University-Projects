import React, {useContext, useState} from 'react';
import {AuthContext} from "./AuthProvider";
import {IonButton, IonFabButton} from "@ionic/react";
import {getLogger} from "../core";
import {Redirect} from "react-router";

const log = getLogger('Login');

export interface LogoutState{
    loggedOut: boolean;
}

const initialState: LogoutState = {
    loggedOut: false,
}

const Logout: React.FC = () => {
    const [state, setState] = useState<LogoutState>(initialState);
    const { isAuthenticated, logout} = useContext(AuthContext);
    const handleLogout = () => {
        log('Logging out - BYE!!');
        logout?.();
        setState({loggedOut: true});
    }
    if (!isAuthenticated){
        console.log('not logged in')
        return (<Redirect to={{pathname: '/login'}}/>);
    }
    console.log('still logged in')
    return (<IonButton onClick={handleLogout}>Logout</IonButton>);
}

export default Logout;
