%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 211

extern int yylex();
void yyerror(void *s);

extern int changeToken;
extern int yychar;
extern int EOF_flag;

int erroSintatico = 0;
int erroSemantico = 0;

int tokenTipo;

typedef struct no {
    int tipo;
    char *data;
    struct no *prox;
} No;

int hash();
void inserirNo();
int getNode();
void doHash();

void **Hash = NULL;

%}

%union {
    struct {
        char *data;
        int col;
        int lin;
    } token;
}

%token INT
%token COMMA
%token CHAR
%token ID
%token FLOAT
%token EOL

%start S

%%

S: D D_Quote EOL { erroSintatico = 0; return 0; }
    | error      { erroSintatico = 1; return 0; } 
;

D_Quote: D D_Quote { }
        | { } 
;

D: T I { } ;

T: INT      { tokenTipo = INT; }
    | CHAR  { tokenTipo = CHAR; }
    | FLOAT { tokenTipo = FLOAT; } 
;

I: ID { 
    // printf(">> %d %s\n\n", tokenTipo, yylval.token.data);
    if(!getNode())
        inserirNo(); 
}
    | I COMMA ID { 
        // printf("-> %d %s\n\n", tokenTipo, yylval.token.data);
        if(!getNode())
            inserirNo(); 
} ;

%%

void yyerror(void *s) {}

void doHash() {
    for(int i = 0; i < HASH_SIZE; i++) {
        No *head = Hash[i];
        while(head) {
            No *aux = head->prox;
            if(head->data) 
                free(head->data);
            free(head);
            head = aux;
        }
        Hash[i] = NULL; 
    }
}

int hash() {
    int hash = 0;
    for(int i = 0; i < strlen(yylval.token.data); i++)
        hash += yylval.token.data[i];
    return hash % HASH_SIZE;
}

void inserirNo() {
    int index = hash(yylval.token.data);
    No *aux = calloc(1, sizeof(No));
    aux->tipo = tokenTipo;
    aux->data = calloc(strlen(yylval.token.data) + 1, sizeof(char));
    strcpy(aux->data, yylval.token.data);

    No *head = (No*) Hash[index];
    if(!head) {
        Hash[index] = aux;
    } else {
        while(head->prox) 
            head = head->prox;
        head->prox = aux;
    }

}

int getNode() {
    if(!Hash) 
        return 0;
    int index = hash(yylval.token.data);
    int ocorrencia = 0;
    No *aux = (No*) Hash[index];

    while(aux) {
        if(!strcmp(yylval.token.data, aux->data)) { // existe outro identificador na hash
            ocorrencia++;
            if(ocorrencia == 1) 
                continue;  
            if(tokenTipo == aux->tipo) {  // mesmo tipo
                if(changeToken) 
                    printf("\n");
                printf("%d: identifier '%s' already declared", yylval.token.lin, yylval.token.data);
                erroSemantico = 1;
                changeToken = 1;
                return 1;
            } else {  // tipos diferentes
                if(changeToken) 
                    printf("\n");
                printf("%d: redefinition of identifier '%s'", yylval.token.lin, yylval.token.data);
                erroSemantico = 1;
                changeToken = 1;
                return 1;
            }
        }
        aux = aux->prox;
    }
    return 0;
}


int main(int argc, char *argv[]) {
    Hash = calloc(HASH_SIZE, sizeof(No));
    while(!EOF_flag) {
        yyparse();

        if(yychar == 0) 
            break;
        if(erroSemantico == 0) {
            if(changeToken) 
                printf("\n");
            printf("%d: All Identifiers on Hash.", yylval.token.lin);
            changeToken = 1;
            doHash();
        } else {
            erroSemantico = 0;
            doHash();
        }        
    }
    if(Hash) {
        doHash(Hash);
        free(Hash);
    }

    return 0;
}