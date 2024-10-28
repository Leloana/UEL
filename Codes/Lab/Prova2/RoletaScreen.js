import React, { useState } from 'react';
import { View, TouchableOpacity,StyleSheet, Image, Text, TextInput, Modal, TouchableWithoutFeedback, Alert ,Keyboard} from 'react-native';
import { checkWinningConditions, checkAposta } from './GameLogic';

const RoletaScreen = ({ saldo, adicionarSaldo, removerSaldo }) => {
  const [numbers, setNumbers] = useState(Array(9).fill(0));
  const [aposta, setAposta] = useState('');
  const [selectedImage, setSelectedImage] = useState(null);

  function generateRandomNumbers() {
    let randomNumbers = [];
    for (let i = 0; i < 9; i++) {
      randomNumbers.push(Math.floor(Math.random() * 5));
    }
    return randomNumbers;
  }

  function handleGenerateNumbers() {
    if (aposta.trim() !== '') {
      const valorAposta = parseInt(aposta);
      if (valorAposta > 0 && valorAposta <= saldo) {
        const newNumbers = generateRandomNumbers();
        setNumbers(newNumbers);
        setSelectedImage(null);

        let odd = checkAposta(newNumbers);
        console.log(odd);
        if (odd === 1000) {
          alert('Parabéns!', 'Grande Ganho!'); // Exibe uma mensagem de alerta na tela
        }

        if (odd === 0) {
          removerSaldo(valorAposta);
        } else {
          adicionarSaldo(valorAposta * odd);
        }

        checkWinningConditions(newNumbers, setNumbers);
      } else {
        alert('Por favor, insira um valor válido para a aposta.');
      }
    } else {
      alert('Por favor, insira um valor para a aposta.');
    }
  }
  const handlePressOutside = () => {
    Keyboard.dismiss(); // Fecha o teclado quando o usuário clica fora do TextInput
  };

  // Mapeamento entre os números e os caminhos das imagens
  const numberImages = {
    0: require('./assets/0.png'),
    1: require('./assets/1.png'),
    2: require('./assets/2.png'),
    3: require('./assets/3.png'),
    4: require('./assets/4.png'),
  };

  return (
    <TouchableWithoutFeedback>
      <View style={styles.container}>
        <Text style={styles.heading}>ROLETA</Text>
        <View style={styles.gridContainer}>
          {numbers.map((item, index) => (
            <TouchableOpacity
              key={index}
              style={[
                styles.cell,
                item.highlighted ? styles.highlightedCell : null,
              ]}
              onPress={() => {
                item.highlighted ? setSelectedImage(numberImages[item.value]) : setSelectedImage(numberImages[item])
              }}
            >
              {item.highlighted ? (
                <View style={styles.highlightedNumber}>
                  <Image source={numberImages[item.value]} style={styles.image} />
                </View>
              ) : (
                <Image source={numberImages[item]} style={styles.image} />
              )}
            </TouchableOpacity>
          ))}
        </View>
        <Text style={styles.saldo}>Saldo: R${saldo.toString()}</Text>
        <TextInput
          style={styles.input}
          value={aposta}
          onChangeText={setAposta}
          keyboardType="numeric"
          placeholder="Valor da aposta"
        />
        <TouchableOpacity onPress={handleGenerateNumbers}>
          <View style={styles.buttonAp}>
            <Text>Apostar</Text>
          </View>
        </TouchableOpacity>

        <Modal visible={selectedImage !== null} transparent>
          <TouchableWithoutFeedback onPress={() => setSelectedImage(null)}>
            <View style={styles.modalContainer}>
              <Image source={selectedImage} style={styles.modalImage} resizeMode="contain" />
            </View>
          </TouchableWithoutFeedback>
        </Modal>
      </View>
    </TouchableWithoutFeedback>

  );
};

const styles = StyleSheet.create({
  heading: {
    color: 'brown',
    fontSize: 40,
    marginBottom: 10,
    alignSelf: 'center',
  },
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#FFFACD',
  },
  title: {
    fontSize: 24,
    marginBottom: 20,
  },
  gridContainer: {
    flexDirection: 'row',
    flexWrap: 'wrap',
    justifyContent: 'center',
    alignItems: 'center',
    marginBottom: 20,
  },
  cell: {
    width: 100,
    height: 100,
    justifyContent: 'center',
    alignItems: 'center',
    margin: 5,
    backgroundColor: 'white',
    borderRadius: 10,
    borderWidth: 2,
    borderColor: 'black',
  },
  highlightedCell: {
    backgroundColor: 'yellow',
  },
  image: {
    width: 80,
    height: 80,
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
    color: 'black',
    backgroundColor: 'white', // Cor de fundo do input
  },
  saldo: {
    marginBottom: 10,
    fontSize: 20,
    color: 'black',
  },
  modalContainer: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: 'rgba(0, 0, 0, 0.5)',
  },
  modalImage: {
    width: '80%',
    height: '80%',
  },
  buttonAp: {
    alignItems: 'center',
    justifyContent: 'center',
    paddingVertical: 12,
    paddingHorizontal: 24,
    borderRadius: 20,
    borderWidth: 2,
    backgroundColor:'brown' ,
    elevation: 3,
  },
});

export default RoletaScreen;
