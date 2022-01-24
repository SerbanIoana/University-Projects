import React from 'react';
import {useNetwork} from "../core/useNetwork";
import {IonItem} from "@ionic/react";

const MyNetwork: React.FC = () => {
    const {networkStatus} = useNetwork();
    return (
        <IonItem class="network">
            <div>Network status is {JSON.stringify(networkStatus)}</div>
        </IonItem>
    );
}

export default MyNetwork;
