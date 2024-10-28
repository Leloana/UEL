%option noyywrap
%{
    #include <stdio.h>
    int newLine = 0;
%}

%%

"if"                                        { 
    if(newLine) printf("\n"); 
    printf("%s IF", yytext); 
    newLine = 1; 
    }
[a-z][a-z0-9]*                              {
     if(newLine) printf("\n"); 
     printf("%s ID", yytext); 
     newLine = 1; 
     }
\.[0-9]+                                    { 
    if(newLine) printf("\n"); 
    printf("%s REAL", yytext); 
    newLine = 1; 
    }
\.                                          { 
    if(newLine) printf("\n"); 
    printf("%s error", yytext); 
    newLine = 1; 
    }
[0-9]+\.[0-9]*                              { 
    if(newLine) printf("\n"); 
    printf("%s REAL", yytext); 
    newLine = 1; 
    }
[0-9]+                                      { 
    if(newLine) printf("\n"); 
    printf("%s NUM", yytext); 
    newLine = 1; 
    }
--[a-z]*\n                                  { 
    if(newLine) printf("\n"); 
    size_t len = strlen(yytext); 
    if (len > 0) yytext[len - 1] = '\0'; 
    printf("%s comment", yytext); 
    newLine = 1; 
    }
[ \t\r]+                                        { 
    if(newLine) printf("\n"); 
    printf("white space"); 
    newLine = 1; 
    }
.                                           { 
    if(newLine) printf("\n"); 
    printf("%s error", yytext); 
    newLine = 1; 
    }

%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}