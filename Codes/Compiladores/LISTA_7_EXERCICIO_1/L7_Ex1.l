%{
    #include <stdio.h>
    #include <stdbool.h>
    int newLine = 0;
%}

%option noyywrap

%%
<<EOF>>         {return 0;}
[\n\r\t]        { /* Ignora novas linhas */ }
\+              {
    if(newLine) printf("\n"); 
    printf("+"); 
    newLine = 1;
    }
\-              { 
    if(newLine) printf("\n");    
    printf("-"); 
    newLine = 1;
    }
[a-z]+[0-9]*           {
    if(newLine) printf("\n"); 
    printf("%s", yytext); 
    newLine = 1;
    }
[0-9]+((e\+|e\-|e)[0-9]+)?  {
    if(newLine) printf("\n"); 
    printf("%s", yytext); 
    newLine = 1;
    }

.               { 
    if(newLine) printf("\n");
    printf("ERRO"); 
    newLine = 1;
    }

%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}
