import React from 'react';
import { View, Text, StyleSheet, ScrollView } from 'react-native';
import CenterMessage from './CenterMessage';

class History extends React.Component {
  render() {
    const { results } = this.props;
    return (
      <ScrollView contentContainerStyle={[!results.length && { flex: 1 }]}>
        <View style={[!results.length && { justifyContent: 'center', flex: 1 }]}>
          {
            !results.length && <CenterMessage message='No results yet!' />
          }
          {
            results.map((item, index) => (
              <View key={index} style={styles.resultContainer}>
                <Text style={styles.names}>{item.name1} & {item.name2}</Text>
                <View style={styles.detailsContainer}>
                  <Text style={styles.percentage}>{item.percentage}%</Text>
                  <Text style={styles.message}>{item.message}</Text>
                </View>
              </View>
            ))
          }
        </View>
      </ScrollView>
    );
  }
}

const styles = StyleSheet.create({
  resultContainer: {
    padding: 10,
    marginVertical: 5,
    borderWidth: 1,
    borderColor: '#ff69b4',
    borderRadius: 20,
    backgroundColor: 'rgba(255,105,180,0.1)',
  },
  names: {
    fontSize: 20,
    fontWeight: 'bold',
    color: 'black',
  },
  detailsContainer: {
    flexDirection: 'row',
    alignItems: 'center',
    marginTop: 5,
  },
  percentage: {
    fontSize: 18,
    marginRight: 10,
    color: 'rgba(0, 0, 0, .5)',
  },
  message: {
    fontSize: 16,
    color: 'rgba(0, 0, 0, .7)',
  },
});

export default History;
