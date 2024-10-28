import React from 'react';
import {
  View,
  Text,
  StyleSheet,
  TouchableWithoutFeedback,
  ScrollView,
} from 'react-native';

export default class Historico extends React.Component {
  navigate = (item) => {
    this.props.navigation.navigate('Historico', { historico: item });
  };

  render() {
    const { historico } = this.props;
    console.log('historico', this.props.historico);
    return (
      <View style={[styles.container]}>
        <ScrollView contentContainerStyle={[!historico.length && { flex: 1 }]}>
          <View style={[!historico.length && { justifyContent: 'center', flex: 1 }]}>
            {historico.map((item, index) => (
              <TouchableWithoutFeedback onPress={() => this.navigate(item)} key={index}>
                <View style={[styles.historicoContainer, { backgroundColor: item.adicionado >= 0 ? 'green' : 'red' }]}>
                  <Text style={styles.newTexto}>Saldo Anterior: {item.saldoAnterior}</Text>
                  <Text style={styles.newTexto}>{item.adicionado >= 0 ? 'Depósito' : 'Saque'}: {Math.abs(item.adicionado)}</Text>
                  <Text style={styles.newTexto}>Novo Saldo: {item.saldoAnterior + item.adicionado}</Text>
                </View>
              </TouchableWithoutFeedback>
            ))}
          </View>
        </ScrollView>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    backgroundColor: '#FFFACD',
  },
  historicoContainer: {
    padding: 10,
    borderBottomWidth: 10,
    borderBottomColor: 'white',
  },
  newTexto: {
    fontSize: 20,
  }
});
