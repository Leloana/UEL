import 'react-native-gesture-handler';
import React, { Component } from 'react'
import CitiesNavScreen from './src/CitiesNavScreen'
import { NavigationContainer } from '@react-navigation/native'
import { createMaterialBottomTabNavigator } from '@react-navigation/material-bottom-tabs';
import AddCity from './src/AddCity'


const Tab = createMaterialBottomTabNavigator()


export default class App extends Component{


 state = {
   cities: []
 }


 addCity = (city) => {
   const cities = this.state.cities
   cities.push(city)
   this.setState({ cities })
   console.log('estado do app.js: ', this.state)
 }
  addLocation = (location, city) => {
   const index = this.state.cities.findIndex(item => {
     return item.id === city.id
   })
   const chosenCity = this.state.cities[index]
   chosenCity.locations.push(location)
   const cities = [
     ...this.state.cities.slice(0, index),
     chosenCity,
     ...this.state.cities.slice(index + 1)
   ]
   this.setState({
     cities
   })
 }
  render(){
   return(
     <NavigationContainer>
       <Tab.Navigator>
         <Tab.Screen name='List Cities'>
           {props => <CitiesNavScreen {...props}
           cities={this.state.cities}
           addLocation={this.addLocation}/>}
         </Tab.Screen>
         <Tab.Screen name='Add City'>
           {() => <AddCity addCity={this.addCity}/>}
       </Tab.Screen>


       </Tab.Navigator>
     </NavigationContainer> 
   )
 }
}

