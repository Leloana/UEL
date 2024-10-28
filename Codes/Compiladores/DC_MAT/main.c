#include <stdio.h>

int yyparse();

int main() {
    printf("DCMAT - Digite 'quit' para sair.\n>");
    yyparse();
    return 0;
}
