import 'react-native-gesture-handler';
import React, { Component } from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { createMaterialBottomTabNavigator } from '@react-navigation/material-bottom-tabs';
import AddNames from './AddNames';
import History from './History';

const Tab = createMaterialBottomTabNavigator();

export default class App extends Component {
  state = {
    results: []
  };

  addResult = (result) => {
    const results = [...this.state.results, result];
    this.setState({ results });
  };

  render() {
    return (
      <NavigationContainer>
        <Tab.Navigator>
          <Tab.Screen name='Add Names'>
            {props => <AddNames {...props} addResult={this.addResult} />}
          </Tab.Screen>
          <Tab.Screen name='History'>
            {props => <History {...props} results={this.state.results} />}
          </Tab.Screen>
        </Tab.Navigator>
      </NavigationContainer>
    );
  }
}
