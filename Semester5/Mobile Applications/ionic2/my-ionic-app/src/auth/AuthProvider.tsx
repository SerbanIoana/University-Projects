import React, {useCallback, useEffect, useState} from 'react';
import PropTypes from 'prop-types';
import {getLogger} from '../core';
import {login as loginApi} from './authApi';
import { Storage } from '@capacitor/storage';

const log = getLogger('AuthProvider');

type LoginFn = (username?: string, password?: string) => void;
type LogoutFn = () => void;

export interface AuthState {
    authenticationError: Error | null;
    isAuthenticated: boolean;
    isAuthenticating: boolean;
    login?: LoginFn;
    logout?:LogoutFn;
    pendingAuthentication?: boolean;
    username?: string;
    password?: string;
    token: string;
    leavingApp: boolean;
}

const initialState: AuthState = {
    isAuthenticated: false,
    isAuthenticating: false,
    authenticationError: null,
    pendingAuthentication: false,
    token: '',
    leavingApp: false
};

export const AuthContext = React.createContext<AuthState>(initialState);

interface AuthProviderProps {
    children: PropTypes.ReactNodeLike,
}

export const AuthProvider: React.FC<AuthProviderProps> = ({children}) => {
    const [state, setState] = useState<AuthState>(initialState);
    const {isAuthenticated, isAuthenticating, authenticationError, pendingAuthentication, token, leavingApp} = state;
    const login = useCallback<LoginFn>(loginCallback, []);
    const logout = useCallback<LogoutFn>(logOutCallback, []);
    useEffect(authenticationEffect, [pendingAuthentication]);
    useEffect(loggingOutEffect, [leavingApp]);
    const value = {isAuthenticated, login, isAuthenticating, authenticationError, token, logout, leavingApp};
    log('render');
    return (
        <AuthContext.Provider value={value}>
            {children}
        </AuthContext.Provider>
    );

    function loginCallback(username?: string, password?: string): Promise<any> {
        log('login');
        setState({
            ...state,
            pendingAuthentication: true,
            username,
            password
        });
        return Promise.resolve();
    }

    function logOutCallback() {
        log('logout');
        setState({
            ...state,
            isAuthenticated:false,
            username:'',
            password:'',
            token:'',
            leavingApp: true
        });
    }

    function loggingOutEffect() {
        let canceled = false;
        logOut();
        return () => {
            canceled = true;
        }

        async function logOut() {
            if (leavingApp){
                try {
                    if (canceled){
                        return ;
                    }
                    Storage.remove({key: 'user'});

                } catch (error){
                    if (canceled){
                        return ;
                    }
                }
            }
        }
    }

    function authenticationEffect() {
        let canceled = false;
        authenticate();
        return () => {
            canceled = true;
        }

        async function authenticate() {
            let existingToken;
            if (!isAuthenticated){
                existingToken = await Storage.get({key: 'user'});
                if (existingToken.value){
                    setState({
                        ...state,
                        pendingAuthentication:true
                    });
                }
            }

            if (!pendingAuthentication) {
                log('authenticate, !pendingAuthentication, return');
                return;
            }

            try {
                log('authenticate...');
                setState({...state, isAuthenticating: true});
                const {username, password} = state;

                if (canceled) {
                    return;
                }
                log('authenticate succeeded');
                let newTokenValue = '';
                if (!existingToken?.value){
                    const {token} = await loginApi(username, password);

                    await Storage.set({
                        key: 'user',
                        value: token,
                    });
                    newTokenValue = token;
                } else{
                    newTokenValue = existingToken.value;
                }

                console.log('ADDED TOKEN TO STATE:' + newTokenValue);
                setState({
                    ...state,
                    token: newTokenValue,
                    pendingAuthentication: false,
                    isAuthenticated: true,
                    isAuthenticating: false
                });
            } catch (error) {
                if (canceled) {
                    return;
                }
                log('authenticate failed');
                setState({
                    ...state,
                    authenticationError: error,
                    pendingAuthentication: false,
                    isAuthenticating: false,
                });
            }
        }
    }
};
