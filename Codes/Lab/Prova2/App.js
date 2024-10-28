import 'react-native-gesture-handler';
import React, { Component, useState } from 'react'
import { NavigationContainer } from '@react-navigation/native'
import { createMaterialBottomTabNavigator } from '@react-navigation/material-bottom-tabs';
import RoletaScreen from './RoletaScreen';
import PerfilScreen from './PerfilScreen';
import HistoricoNavScreen from './HistoricoNavScreen';

const Tab = createMaterialBottomTabNavigator()


export default class App extends Component{
 state = {
   saldo: 0,
   historico: [],
 }
 addHistorico = (transacao) => {
    const historico = this.state.historico
    historico.push(transacao)
    this.setState({ historico })
    console.log('estado do app.js: ', this.state)
  }

 adicionarSaldo = (valor) => {
    this.setState((prevState) => ({
      saldo: prevState.saldo + valor,
    }));
  };

  removerSaldo = (valor) => {
    this.setState((prevState) => ({
      saldo: prevState.saldo - valor,
    }));
  };
  render(){
   return(
     <NavigationContainer>
       <Tab.Navigator>
         <Tab.Screen name='Roleta'>
           {props => <RoletaScreen {...props}
           saldo={this.state.saldo}
           adicionarSaldo={this.adicionarSaldo}
           removerSaldo={this.removerSaldo}/>}
         </Tab.Screen>
         <Tab.Screen name='Perfil'>
           {props => <PerfilScreen {...props}
           saldo={this.state.saldo}
           adicionarSaldo={this.adicionarSaldo}
           removerSaldo={this.removerSaldo}
           addHistorico={this.addHistorico}/>}
       </Tab.Screen>
       <Tab.Screen name='Historico'>
           {props => <HistoricoNavScreen {...props}
           historico={this.state.historico}/>}
       </Tab.Screen>
       </Tab.Navigator>
     </NavigationContainer> 
   )
 }
}