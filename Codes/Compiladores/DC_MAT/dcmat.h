#ifndef DCMAT_H
#define DCMAT_H

#include <math.h>
#include <stdio.h>

#define MAX_VARS 100

typedef struct {
    char name[50];
    double value;
} Variable;

// Protótipos de funções
double get_var_value(const char *name);
void set_var_value(const char *name, double value);
double calculate_integral(double lower, double upper, double (*func)(double));
double sum_function(int lower, int upper, double (*func)(int));
double example_function(int x); // Atualizado para double
void plot_function(double (*func)(double), double start, double end);

#endif
