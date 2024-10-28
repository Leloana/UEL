import React from 'react';
import { View, Text, StyleSheet, TextInput, TouchableOpacity, Alert, Keyboard } from 'react-native';

class AddNames extends React.Component {
  state = {
    name1: '',
    name2: '',
    percentage: null,
    message: '',
    animatedPercentage: 0,
  };

  intervalId = null;

  componentDidMount() {
    if (this.state.percentage !== null) {
      this.intervalId = setInterval(this.updatePercentage, 50);
    }
  }

  componentWillUnmount() {
    if (this.intervalId !== null) {
      clearInterval(this.intervalId);
    }
  }

  updatePercentage = () => {
    const { percentage } = this.state;
    if (this.state.animatedPercentage < percentage) {
      const newPercentage = this.state.animatedPercentage + 1;
      const message = this.getMessage(newPercentage);
      this.setState({ animatedPercentage: newPercentage, message });
    } else {
      clearInterval(this.intervalId);
    }
  };

  onChangeText = (key, value) => {
    this.setState({ [key]: value });
  };

  getMessage = (percentage) => {
    if (percentage === 100) return '💖 Juntos pela eternidade';
    if (percentage === 0) return '💀';
    if (percentage >= 90) return 'Casal perfeito';
    if (percentage >= 80) return 'Casal sensacional';
    if (percentage >= 70) return 'Casal bom';
    if (percentage >= 60) return 'Casal legal';
    if (percentage >= 50) return 'Casal ok';
    if (percentage >= 40) return 'Casal de 1 mês';
    if (percentage >= 30) return 'Casal meia bomba';
    if (percentage >= 20) return 'Casal ruim';
    if (percentage >= 10) return 'Casal horrível';
    return 'Casal detestável';
  };

  calculateLove = () => {
    const { name1, name2 } = this.state;
    if (name1 === '' || name2 === '') {
      Alert.alert('Please enter both names');
      return;
    }
    const hash = this.getHash(name1, name2);
    // Usar o hash para gerar uma porcentagem consistente
    const percentage = Math.floor((hash % 101 + 101) % 101);
    const message = this.getMessage(percentage);
    const result = { name1, name2, percentage, message };
    this.props.addResult(result);
    this.setState({ percentage, message, animatedPercentage: 0 });
    this.intervalId = setInterval(this.updatePercentage, 50);

    // Dismiss the keyboard after calculating love
    Keyboard.dismiss();
  };

  getHash = (name1, name2) => {
    let hash = 0;
    for (let i = 0; i < name1.length; i++) {
      hash += name1.charCodeAt(i) * 31;
    }
    for (let j = 0; j < name2.length; j++) {
      hash += name2.charCodeAt(j) * 31;
    }
    return hash;
  };

  render() {
    const { name1, name2, percentage, message, animatedPercentage } = this.state;
    return (
      <View style={styles.container}>
        <View style={styles.messageContainer}>
          {message !== '' && (
            <Text style={styles.messageText}>{message}</Text>
          )}
        </View>
        <View style={styles.circleContainer}>
          <View style={[styles.circle, { backgroundColor: 'white' }]}>
            <View style={[styles.filler, { height: `${animatedPercentage}%` }]} />
            <Text style={styles.percentageText}>{percentage !== null ? `${animatedPercentage}%` : ''}</Text>
          </View>
        </View>
        <View style={styles.inputContainer}>
          <TextInput
            placeholder='Name 1'
            onChangeText={val => this.onChangeText('name1', val)}
            style={styles.input}
            value={name1}
          />
          <TextInput
            placeholder='Name 2'
            onChangeText={val => this.onChangeText('name2', val)}
            style={styles.input}
            value={name2}
          />
        </View>
        <TouchableOpacity onPress={this.calculateLove}>
          <View style={styles.heartButton}>
            <Text style={styles.buttonText}>💖 Calcular</Text>
          </View>
        </TouchableOpacity>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: 'white',
    backgroundImage: 'url("./assets/fundo-coracao.jpg")',
  },
  circleContainer: {
    alignItems: 'center',
    marginBottom: 20,
  },
  circle: {
    width: 150,
    height: 150,
    borderRadius: 75,
    borderWidth: 2,
    borderColor: 'black',
    justifyContent: 'center',
    alignItems: 'center',
    position: 'relative',
    overflow: 'hidden',
  },
  filler: {
    position: 'absolute',
    bottom: 0,
    left: 0,
    right: 0,
    backgroundColor: 'pink',
  },
  percentageText: {
   
    fontSize: 50,
    color: 'black',
    zIndex: 1,
  },
  messageContainer: {
    marginBottom: 20,
  },
  messageText: {
    fontSize: 24,
    fontWeight: 'bold',
    textAlign: 'center',
  },
  inputContainer: {
    flexDirection: 'row',
    marginBottom: 20,
  },
  input: {
    flex: 1,
    marginHorizontal: 5,
    paddingHorizontal: 8,
    height: 50,
    borderRadius: 10,
    borderWidth: 1,
    borderColor: 'black',
    backgroundColor: 'white',
    color: 'black',
  },
  heartButton: {
    width: 150,
    height: 50,
    borderWidth: 1,
    borderColor: 'black',
    backgroundColor: '#ff69b4',
    justifyContent: 'center',
    alignItems: 'center',
    borderRadius: 25,
    overflow: 'hidden',
  },
  buttonText: {
    color: 'white',
    fontSize: 18,
  },
});

export default AddNames;
