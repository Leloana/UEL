#include <stdio.h>
#include <math.h>
#include <string.h>
#include "dcmat.h"

// Definição das variáveis globais
Variable vars[MAX_VARS];
int var_count = 0;

// Função para obter o valor de uma variável
double get_var_value(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            return vars[i].value;
        }
    }
    fprintf(stderr, "Erro: Variável '%s' não definida.\n", name);
    return 0;
}

// Função para definir o valor de uma variável
void set_var_value(const char *name, double value) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            vars[i].value = value;
            return;
        }
    }
    strcpy(vars[var_count].name, name);
    vars[var_count].value = value;
    var_count++;
}

// Função de exemplo para somatório e integral
double example_function(int x) {
    return sin(x);  // Exemplo com seno; você pode ajustar para outra função.
}

// Função de integral usando método trapezoidal
double calculate_integral(double lower, double upper, double (*func)(double)) {
    int steps = 1000;  // Número de passos para aumentar a precisão
    double step = (upper - lower) / steps;
    double sum = 0.0;
    for (int i = 0; i < steps; i++) {
        double x1 = lower + i * step;
        double x2 = x1 + step;
        sum += (func(x1) + func(x2)) / 2 * step;
    }
    return sum;
}

// Função de somatório com variável de índice local
double sum_function(int lower, int upper, double (*func)(int)) {
    double sum = 0;
    for (int i = lower; i <= upper; i++) {
        sum += func(i);  // func(i) agora usa o índice `i` diretamente
    }
    return sum;
}

// Função de plotagem simulada
void plot_function(double (*func)(double), double start, double end) {
    printf("Plotando função de %f a %f:\n", start, end);
    for (double x = start; x <= end; x += (end - start) / 40) {  // 40 pontos para o gráfico
        int value = (int)(20 * func(x));  // Multiplica para ajustar a escala
        for (int i = 0; i < value + 20; i++) printf(" ");
        printf("*\n");
    }
}
