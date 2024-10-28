export function checkWinningConditions(numbers, setNumbers) {
  let winningRows = [];
  // Verificando linhas
  for (let i = 0; i < 9; i += 3) {
    if (numbers[i] === numbers[i + 1] && numbers[i] === numbers[i + 2]) {
      winningRows.push([i, i + 1, i + 2]);
    }
  }
  // Verificando colunas
  for (let i = 0; i < 3; i++) {
    if (numbers[i] === numbers[i + 3] && numbers[i] === numbers[i + 6]) {
      winningRows.push([i, i + 3, i + 6]);
    }
  }
  // Verificando diagonais
  if (numbers[0] === numbers[4] && numbers[0] === numbers[8]) {
    winningRows.push([0, 4, 8]);
  }
  if (numbers[2] === numbers[4] && numbers[2] === numbers[6]) {
    winningRows.push([2, 4, 6]);
  }
  // Destaca todas as fileiras vitoriosas
  const updatedNumbers = [...numbers];
  winningRows.forEach(row => {
    row.forEach(index => {
      // Se o numero nao estiver destacado ainda
      if(!updatedNumbers[index].highlighted)updatedNumbers[index] = { value: updatedNumbers[index], highlighted: true };
    });
  });
  setNumbers(updatedNumbers);
}

//Fileiras simples dao 1 ponto cada
//Diagonais dao 5 cada 
//Caso todas as celulas estejam completas tem um ganho de 1000
export function checkAposta(numbers){
  // Verificando linhas
  let num = 0;
  for (let i = 0; i < 9; i += 3) {
    if (numbers[i] === numbers[i + 1] && numbers[i] === numbers[i + 2]) {
      num ++;
    }
  }
  // Verificando colunas
  for (let i = 0; i < 3; i++) {
    if (numbers[i] === numbers[i + 3] && numbers[i] === numbers[i + 6]) {
      num ++;
    }
  }
  // Verificando diagonais
  if (numbers[0] === numbers[4] && numbers[0] === numbers[8]) {
    num += 5;
  }
  if (numbers[2] === numbers[4] && numbers[2] === numbers[6]) {
    num += 5;
  }
  //Caso a jogada seja perfeita (Todas as celulas com o mesmo valor)
  if(num == 16) num = 1000;
  // Se nenhuma condição de vitória for atendida, limpa o estado de vitória
  return num;
  }
  
  
  