#ifndef _SINTATICO_H
#define _SINTATICO_H

#include "lexico.h"

//DEFININDO TOKENS


#define ID 2 
#define NUM_INT 3
#define NUM_REAL 4
#define PONTO_VIRGULA 5
#define VIRGULA 6
#define DOIS_PONTOS 7
#define PONTO 8
#define ABRE_COLCHETE 9
#define FECHA_COLCHETE 10
#define ABRE_PARENTESES 11
#define FECHA_PARENTESES 12
#define IGUAL 13
#define MAIOR 14
#define MENOR 15
#define MAIS 16
#define MENOS 17
#define VEZES 18
#define DIVISAO 19
#define ALGORITMO 28
#define ATE 30
#define DIFERENTE 31
#define MAIOR_IGUAL 32
#define MENOR_IGUAL 33
#define ATRIBUICAO 34
#define INICIO 40
#define IMPRIMA 46
#define FIM 49
#define FUNCAO 54
#define FACA 57
#define FALSO 60
#define VARIAVEIS 69
#define VETOR 73
#define VERDADEIRO 81
#define INTEIRO 86
#define REAL 90
#define REPITA 94
#define SE 96
#define SENAO 99
#define E 100
#define ENTAO 104
#define ENQUANTO 110
#define DE 112
#define DIV 114
#define OU 116
#define NAO 119
#define TIPO 123
#define LEIA 127
#define LOGICO 132
#define MATRIZ 138
#define CARACTERE 147
#define PARA 151
#define PASSO 154
#define PROCEDIMENTO 165
#define COMENTARIO_LINHA 166
#define STRING 168
#define COMENTARIO_BLOCO 170
#define EOF_TOKEN 2004

// excessao string e comentario bloco

//  ========== PARSER ==========
/*
 Nome da funcao: parser

 Descrição:
 Função principal que inicia o processo de análise sintática. Obtém o próximo token da pilha
 e inicia a análise começando pelo símbolo inicial. Caso a pilha esteja vazia, imprime uma
 mensagem de erro e encerra o programa.

 Parâmetros:
 - tokens: estrutura de dados que armazena a pilha de tokens a ser analisada.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void parser(void *cadeia, char *input);
/*
 Nome da funcao: eat

 Descrição:
 Compara o token atual com o token esperado (tokenAnalisado). Se os tokens coincidirem,
 o token é removido da pilha e o próximo token é carregado. Caso contrário, imprime uma
 mensagem de erro de sintaxe, libera a pilha e encerra o programa.

 Parâmetros:
 - tokens: estrutura de dados que armazena a pilha de tokens a ser analisada.
 - tokenAnalisado: o token esperado que deve ser comparado com o token atual.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void eat(void *cadeia, int tokenAnalisado, char *input);
/*
 Nome da funcao: erroSintaxe

 Descrição:
 Imprime uma mensagem de erro de sintaxe indicando a linha e coluna do token que causou
 o erro. Não encerra o programa, apenas imprime o erro.

 Parâmetros:
 - tokens: estrutura de dados que armazena a pilha de tokens a ser analisada.
 */
void erroSintaxe(void *cadeia);
/*
 Nome da funcao: defineID
 
 Descrição:
 Processa a definição de um identificador (ID), geralmente usado para armazenar o nome
 de variáveis ou funções no código.

 Parâmetros:
 Nenhum.
 */
void defineID();

/*
 Nome da funcao: S
 
 Descrição:
 Ponto de partida do processo de análise sintática. Chama as demais funções necessárias
 para validar a estrutura do código de acordo com a gramática.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void S(void *cadeia, char *input);  

/*
 Nome da funcao: identifyPROGRAMA
 
 Descrição:
 Analisa a estrutura geral de um identifyPROGRAMA, verificando as partes principais como declarações
 e procedimentos.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */      
void identifyPROGRAMA(void *cadeia, char *input);      

/*
 Nome da funcao: identifyFuncao
 
 Descrição:
 Verifica se a definição de procedimentos ou funções está correta, conforme a sintaxe da
 linguagem.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */  
void identifyFuncao(void *cadeia, char *input);          

/*
 Nome da funcao: identifyPocedimento
 
 Descrição:
 Analisa a sintaxe de uma declaração de procedimento, incluindo nome, parâmetros e corpo.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void identifyPocedimento(void *cadeia, char *input);        

/*
 Nome da funcao: declareFuncao
 
 Descrição:
 Analisa a sintaxe de uma declaração de função, incluindo tipo de retorno, nome, parâmetros
 e corpo da função.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void declareFuncao(void *cadeia, char *input);

/*
 Nome da funcao: identifyPARAMETROS
 
 Descrição:
 Verifica a sintaxe de uma lista de parâmetros de um procedimento ou função.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void identifyPARAMETROS(void *cadeia, char *input);   

/*
 Nome da funcao: declarePARAMETROS
 
 Descrição:
 Analisa a declaração individual de parâmetros em um procedimento ou função.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void declarePARAMETROS(void *cadeia, char *input); 

/*
 Nome da funcao: identifyBLOCOS
 
 Descrição:
 Verifica a declaração de variáveis dentro de um bloco de código.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void identifyBLOCOS(void *cadeia, char *input); 

/*
 Nome da funcao: declaring
 
 Descrição:
 Verifica a lista de declarações em um bloco de código, como a criação de variáveis
 ou funções.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void declaring(void *cadeia, char *input);  

/*
 Nome da funcao: declaring_dash
 
 Descrição:
 Análise da lista de declarações recursiva (ex: declarações contínuas).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void declaringDash(void *cadeia, char *input); // declaring'

/*
 Nome da funcao: declareTIPO
 
 Descrição:
 Analisa a declaração de tipos, como tipos básicos ou estruturados.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void declareTIPO(void *cadeia, char *input);  

/*
 Nome da funcao: declareVAR
 
 Descrição:
 Verifica a declaração de variáveis, seus nomes e tipos.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void declareVAR(void *cadeia, char *input);    

/*
 Nome da funcao: declareID
 
 Descrição:
 Analisa um identificador na declaração de uma variável ou função.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void declareID(void *cadeia, char *input); 

/*
 Nome da funcao: declareIDDash
 
 Descrição:
 Analisa identificadores consecutivos, como em uma lista de variáveis.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void declareIDDash(void *cadeia, char *input); // 

/*
 Nome da funcao: identifyVETOR
 
 Descrição:
 Verifica a declaração de vetores ou matrizes e suas dimensões.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void identifyVETOR(void *cadeia, char *input);

/*
 Nome da funcao: identifyDIMENSION
 
 Descrição:
 Analisa a dimensão de um vetor ou matriz.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void identifyDIMENSION(void *cadeia, char *input);    

/*
 Nome da funcao: dimensionDash
 
 Descrição:
 Analisa dimensões consecutivas (ex: vetores de mais de uma dimensão).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void dimensionDash(void *cadeia, char *input); // Dimensoes'

/*
 Nome da funcao: basicTIPO
 
 Descrição:
 Verifica se o tipo de uma variável ou parâmetro é um tipo básico suportado pela linguagem.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void basicTIPO(void *cadeia, char *input);  

/*
 Nome da funcao: identifyBlocoCOMANDOS
 
 Descrição:
 Analisa um bloco de comandos, como laços, condições e expressões.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void identifyBlocoCOMANDOS(void *cadeia, char *input); 

/*
 Nome da funcao: identifyListaCOMANDOS
 
 Descrição:
 Verifica uma lista de comandos sequenciais dentro de um bloco.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void identifyListaCOMANDOS(void *cadeia, char *input);   

/*
 Nome da funcao: listaComandosDash
 
 Descrição:
 Verifica comandos consecutivos (ex: execução contínua de expressões).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void listaComandosDash(void *cadeia, char *input); // identifyListaCOMANDOS'

/*
 Nome da funcao: Comandos
 
 Descrição:
 Verifica a correção de comandos, como atribuições, chamadas de função, etc.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void Comandos(void *cadeia, char *input);     

/*
 Nome da funcao: comandosDash1
 
 Descrição:
 Verifica a sequência de comandos, parte 1 (variações da estrutura de comandos).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void comandosDash1(void *cadeia, char *input); // Comandos'

/*
 Nome da funcao: comandosDash2
 
 Descrição:
 Verifica a sequência de comandos, parte 2 (variações adicionais da estrutura de comandos).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void comandosDash2(void *cadeia, char *input); // Comandos''

/*
 Nome da funcao: comandosDash3
 
 Descrição:
 Verifica a sequência de comandos, parte 3 (variações extras da estrutura de comandos).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void comandosDash3(void *cadeia, char *input); // Comandos'''

/*
 Nome da funcao: identifyEXPRESSAO
 
 Descrição:
 Analisa uma expressão matemática ou lógica no código.

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void identifyEXPRESSAO(void *cadeia, char *input);  

/*
 Nome da funcao: expressaoDash
 
 Descrição:
 Analisa a parte recursiva de uma expressão (ex: operações em sequência).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void expressaoDash(void *cadeia, char *input); // identifyEXPRESSAO'
/*
 Nome da funcao: simpleEXPRESSAO
 
 Descrição:
 Analisa a parte recursiva de uma expressão (ex: operações em sequência).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void simpleEXPRESSAO(void *cadeia, char *input);        
/*
 Nome da funcao: simpleEXPRESSAODash
 
 Descrição:
 Analisa a parte recursiva de uma expressão (ex: operações em sequência).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */   
void simpleEXPRESSAODash(void *cadeia, char *input); // simpleEXPRESSAO'
/*
 Nome da funcao: OperadorRelacional
 
 Descrição:
 Analisa a parte recursiva de uma expressão (ex: operações em sequência).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void OperadorRelacional(void *cadeia, char *input);   
/*
 Nome da funcao: OperadorAritmetico
 
 Descrição:
 Analisa a parte recursiva de uma expressão (ex: operações em sequência).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */    
void OperadorAritmetico(void *cadeia, char *input);    
/*
 Nome da funcao: Termo
 
 Descrição:
 Analisa a parte recursiva de uma expressão (ex: operações em sequência).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */    
void Termo(void *cadeia, char *input);   
/*
 Nome da funcao: termoDash
 
 Descrição:
 Analisa a parte recursiva de uma expressão (ex: operações em sequência).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */         
void termoDash(void *cadeia, char *input); // Termo'
/*
 Nome da funcao: Fator
 
 Descrição:
 Analisa a parte recursiva de uma expressão (ex: operações em sequência).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void Fator(void *cadeia, char *input); 
/*
 Nome da funcao: fatorDash
 
 Descrição:
 Analisa a parte recursiva de uma expressão (ex: operações em sequência).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */       
void fatorDash(void *cadeia, char *input); // Fator'
/*
 Nome da funcao: Variavel
 
 Descrição:
 Analisa a parte recursiva de uma expressão (ex: operações em sequência).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void Variavel(void *cadeia, char *input);    
/*
 Nome da funcao: variavelDash
 
 Descrição:
 Analisa a parte recursiva de uma expressão (ex: operações em sequência).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */       
void variavelDash(void *cadeia, char *input); // Variavel'
/*
 Nome da funcao: ExprIter
 
 Descrição:
 Analisa a parte recursiva de uma expressão (ex: operações em sequência).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */
void ExprIter(void *cadeia, char *input);         
/*
 Nome da funcao: exprIterDash
 
 Descrição:
 Analisa a parte recursiva de uma expressão (ex: operações em sequência).

 Parâmetros:
 - cadeia: estrutura de dados que armazena tokens para análise.
 - input: cadeia de caracteres que representa o código a ser analisado.
 */  
void exprIterDash(void *cadeia, char *input);


#endif