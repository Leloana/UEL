import React from 'react'
import { Text, View, StyleSheet} from 'react-native'


import { colors } from './theme'


const CenterMessage = ({ message }) => (
   <View style={StyleSheet.emptyContainer}>
       <Text style={styles.message}>
           {message}
       </Text>
   </View>
)


const styles = StyleSheet.create({
   emptyContainer:{
       padding: 10,
       borderBottomWidth: 2,
       borderBottomColor: '#1976D2'
   },
   message: {
       alignSelf: 'center',
       fontSize: 20
   }
})


export default CenterMessage
