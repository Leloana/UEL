import React, { useState } from 'react';
import { View, Text, TextInput, StyleSheet, Keyboard ,TouchableOpacity} from 'react-native';

const PerfilScreen = ({ saldo, adicionarSaldo, removerSaldo, addHistorico }) => {
  const [valorTransacao, setValorTransacao] = useState('');

  const depositar = () => {
    const valorDeposito = parseFloat(valorTransacao);
    if (!isNaN(valorDeposito) && valorDeposito > 0) {
      addHistorico({saldoAnterior: saldo, adicionado: valorDeposito});
      adicionarSaldo(valorDeposito);
      setValorTransacao('');
      Keyboard.dismiss(); // Fecha o teclado após o depósito
    }
    else{
        alert("Insira um valor válido para o depósito")
    }
  };

  const sacar = () => {
    const valorSaque = parseFloat(valorTransacao);
    if (!isNaN(valorSaque) && valorSaque > 0 && valorSaque <= saldo) {
      addHistorico({saldoAnterior: saldo, adicionado: (-valorSaque)});
      removerSaldo(valorSaque);
      setValorTransacao('');
      Keyboard.dismiss(); // Fecha o teclado após o saque
    }
    else{
      alert("Insira um valor válido para o saque")
  }
  };

  return (
    <View style={styles.container}>
      <Text style={styles.heading}>PERFIL</Text>
      <Text style={styles.saldo}>Saldo: R${saldo.toString()}</Text>
      <TextInput
        style={styles.input}
        onChangeText={setValorTransacao}
        value={valorTransacao}
        keyboardType="numeric"
        placeholder="Valor"
      />
      <View style={styles.buttonsContainer}>
        <TouchableOpacity onPress={depositar}>
          <View style={styles.buttonDep}>
            <Text>Depositar</Text>
          </View>
        </TouchableOpacity>
        <TouchableOpacity onPress={sacar}>
          <View style={styles.buttonSaq}>
            <Text>Sacar</Text>
          </View>
        </TouchableOpacity>
      </View>
    </View>
  );
};

const styles = StyleSheet.create({
  heading: {
    color: 'green',
    fontSize: 40,
    marginBottom: 10,
    alignSelf: 'center',
  },
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
    backgroundColor: '#C6E5B1',
  },
  saldo: {
    marginBottom: 10,
    fontSize: 40,
  },
  input: {
    width: 200,
    height: 40,
    borderColor: 'gray',
    borderWidth: 1,
    borderRadius: 15,
    paddingHorizontal: 10,
    marginBottom: 20,
    fontSize: 20,
    backgroundColor: 'white', // Cor de fundo do input
  },
  buttonsContainer: {
    flexDirection: 'row',
    justifyContent: 'space-around',
    width: '100%',
  },
  buttonDep: {
    alignItems: 'center',
    justifyContent: 'center',
    paddingVertical: 12,
    paddingHorizontal: 24,
    borderRadius: 20,
    borderWidth: 2,
    backgroundColor:'green' ,
    elevation: 3,
  },
  buttonSaq: {
    alignItems: 'center',
    justifyContent: 'center',
    paddingVertical: 12,
    paddingHorizontal: 24,
    borderRadius: 20,
    borderWidth: 2,
    backgroundColor:'red' ,
    elevation: 3,
  },
});

export default PerfilScreen;
