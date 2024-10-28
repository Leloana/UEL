import React from 'react';
import { View, Text, StyleSheet } from 'react-native';

class Historico extends React.Component {
  render() {
    const { saldoAnterior, adicionado } = this.props.route.params.historico;
    const backgroundColor = adicionado >= 0 ? 'green' : 'red';
    return (
      <View style={[styles.container, { backgroundColor }]}>
        <Text style={styles.text}>Saldo Anterior: {saldoAnterior}</Text>
        <Text style={styles.text}>Modificado: {adicionado}</Text>
        <Text style={styles.text}>Novo saldo: {saldoAnterior+adicionado}</Text>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  text: {
    fontSize: 30,
    fontWeight: 'bold',
    color: 'white',
    marginBottom: 10,
  },
});

export default Historico;
