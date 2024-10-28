%{
    #include <stdio.h>

    enum yytokentype {
        VOID = 258,
        INT,
        CHAR,
        RETURN,
        BREAK,
        SWITCH,
        CASE,
        DEFAULT,
        DO,
        WHILE,
        FOR,
        IF,
        ELSE,
        TYPEDEF,
        STRUCT,
        PLUS,
        MINUS,
        MULTIPLY,
        DIV,
        REMAINDER,
        INC,
        DEC,
        BITWISE_AND,
        BITWISE_OR,
        BITWISE_NOT,
        BITWISE_XOR,
        NOT,
        LOGICAL_AND,
        LOGICAL_OR,
        EQUAL,
        NOT_EQUAL,
        LESS_THAN,
        GREATER_THAN,
        LESS_EQUAL,
        GREATER_EQUAL,
        R_SHIFT,
        L_SHIFT,
        ASSIGN,
        ADD_ASSIGN,
        MINUS_ASSIGN,
        SEMICOLON,
        COMMA,
        COLON,
        L_PAREN,
        R_PAREN,
        L_CURLY_BRACKET,
        R_CURLY_BRACKET,
        L_SQUARE_BRACKET,
        R_SQUARE_BRACKET,
        TERNARY_CONDITIONAL,
        NUMBER_SIGN,
        POINTER,
        PRINTF,
        SCANF,
        DEFINE,
        EXIT,
        IDENTIFIER,
        NUM_INTEGER,
        NUM_OCTAL,
        NUM_HEXA,
        STRING,
        CHARACTER,
        ERRO,
        UNCLOSED_COMMENT,
        IDENTIFIER_TOO_LONG,
        WARNING,
        END
    };

    

    const char* getTokenName(int token) {
        switch(token) {
            case VOID: return "VOID";
            case INT: return "INT";
            case CHAR: return "CHAR";
            case RETURN: return "RETURN";
            case BREAK: return "BREAK";
            case SWITCH: return "SWITCH";
            case CASE: return "CASE";
            case DEFAULT: return "DEFAULT";
            case DO: return "DO";
            case WHILE: return "WHILE";
            case FOR: return "FOR";
            case IF: return "IF";
            case ELSE: return "ELSE";
            case TYPEDEF: return "TYPEDEF";
            case STRUCT: return "STRUCT";
            case PLUS: return "PLUS";
            case MINUS: return "MINUS";
            case MULTIPLY: return "MULTIPLY";
            case DIV: return "DIV";
            case REMAINDER: return "REMAINDER";
            case INC: return "INC";
            case DEC: return "DEC";
            case BITWISE_AND: return "BITWISE_AND";
            case BITWISE_OR: return "BITWISE_OR";
            case BITWISE_NOT: return "BITWISE_NOT";
            case BITWISE_XOR: return "BITWISE_XOR";
            case NOT: return "NOT";
            case LOGICAL_AND: return "LOGICAL_AND";
            case LOGICAL_OR: return "LOGICAL_OR";
            case EQUAL: return "EQUAL";
            case NOT_EQUAL: return "NOT_EQUAL";
            case LESS_THAN: return "LESS_THAN";
            case GREATER_THAN: return "GREATER_THAN";
            case LESS_EQUAL: return "LESS_EQUAL";
            case GREATER_EQUAL: return "GREATER_EQUAL";
            case R_SHIFT: return "R_SHIFT";
            case L_SHIFT: return "L_SHIFT";
            case ASSIGN: return "ASSIGN";
            case ADD_ASSIGN: return "ADD_ASSIGN";
            case MINUS_ASSIGN: return "MINUS_ASSIGN";
            case SEMICOLON: return "SEMICOLON";
            case COMMA: return "COMMA";
            case COLON: return "COLON";
            case L_PAREN: return "L_PAREN";
            case R_PAREN: return "R_PAREN";
            case L_CURLY_BRACKET: return "L_CURLY_BRACKET";
            case R_CURLY_BRACKET: return "R_CURLY_BRACKET";
            case L_SQUARE_BRACKET: return "L_SQUARE_BRACKET";
            case R_SQUARE_BRACKET: return "R_SQUARE_BRACKET";
            case TERNARY_CONDITIONAL: return "TERNARY_CONDITIONAL";
            case NUMBER_SIGN: return "NUMBER_SIGN";
            case POINTER: return "POINTER";
            case PRINTF: return "PRINTF";
            case SCANF: return "SCANF";
            case DEFINE: return "DEFINE";
            case EXIT: return "EXIT";
            case IDENTIFIER: return "IDENTIFIER";
            case NUM_INTEGER: return "NUM_INTEGER";
            case NUM_OCTAL: return "NUM_OCTAL";
            case NUM_HEXA: return "NUM_HEXA";
            case ERRO: return "error";
            case UNCLOSED_COMMENT: return "error";
            case IDENTIFIER_TOO_LONG: return "error";
            default: return "UNKNOWN";
        }
    };
    int linha = 1;
    int coluna = 1;
    int iniciaComment = 0;
    int linhasComment = 0;
    int colunasComment = 0;
    int initColunm = 0;
    int initLine = 0;
%}

%option noyywrap

%x COMMENT
%x Char

%%

"void"                  { coluna += yyleng; return VOID; }
"int"                   { coluna += yyleng; return INT; }
"char"                  { coluna += yyleng; return CHAR; }
"return"                { coluna += yyleng; return RETURN; }
"break"                 { coluna += yyleng; return BREAK; }
"switch"                { coluna += yyleng; return SWITCH; }
"case"                  { coluna += yyleng; return CASE; }
"default"               { coluna += yyleng; return DEFAULT; }
"do"                    { coluna += yyleng; return DO; }
"while"                 { coluna += yyleng; return WHILE; }
"for"                   { coluna += yyleng; return FOR; }
"if"                    { coluna += yyleng; return IF; }
"else"                  { coluna += yyleng; return ELSE; }
"typedef"               { coluna += yyleng; return TYPEDEF; }
"struct"                { coluna += yyleng; return STRUCT; }
"+"                     { coluna += yyleng; return PLUS; }
"-"                     { coluna += yyleng; return MINUS; }
"*"                     { coluna += yyleng; return MULTIPLY; }
"/"                     { coluna += yyleng; return DIV; }
"%"                     { coluna += yyleng; return REMAINDER; }
"++"                    { coluna += yyleng; return INC; }
"--"                    { coluna += yyleng; return DEC; }
"&"                     { coluna += yyleng; return BITWISE_AND; }
"|"                     { coluna += yyleng; return BITWISE_OR; }
"~"                     { coluna += yyleng; return BITWISE_NOT; }
"^"                     { coluna += yyleng; return BITWISE_XOR; }
"!"                     { coluna += yyleng; return NOT; }
"&&"                    { coluna += yyleng; return LOGICAL_AND; }
"||"                    { coluna += yyleng; return LOGICAL_OR; }
"=="                    { coluna += yyleng; return EQUAL; }
"!="                    { coluna += yyleng; return NOT_EQUAL; }
"<"                     { coluna += yyleng; return LESS_THAN; }
">"                     { coluna += yyleng; return GREATER_THAN; }
"<="                    { coluna += yyleng; return LESS_EQUAL; }
">="                    { coluna += yyleng; return GREATER_EQUAL; }
">>"                    { coluna += yyleng; return R_SHIFT; }
"<<"                    { coluna += yyleng; return L_SHIFT; }
"="                     { coluna += yyleng; return ASSIGN; }
"+="                    { coluna += yyleng; return ADD_ASSIGN; }
"-="                    { coluna += yyleng; return MINUS_ASSIGN; }
","                     { coluna += yyleng; return COMMA; }
";"                     { coluna += yyleng; return SEMICOLON; }
":"                     { coluna += yyleng; return COLON; }
"("                     { coluna += yyleng; return L_PAREN; }
")"                     { coluna += yyleng; return R_PAREN; }
"{"                     { coluna += yyleng; return L_CURLY_BRACKET; }
"}"                     { coluna += yyleng; return R_CURLY_BRACKET; }
"["                     { coluna += yyleng; return L_SQUARE_BRACKET; }
"]"                     { coluna += yyleng; return R_SQUARE_BRACKET; }
"?"                     { coluna += yyleng; return TERNARY_CONDITIONAL; }
"#"                     { coluna += yyleng; return NUMBER_SIGN; }
"->"                    { coluna += yyleng; return POINTER; }
"printf"                { coluna += yyleng; return PRINTF; }
"scanf"                 { coluna += yyleng; return SCANF; }
"define"                { coluna += yyleng; return DEFINE; }
"exit"                  { coluna += yyleng; return EXIT; }
[a-zA-Z_][a-zA-Z0-9_]*  {if(yyleng> 255)return IDENTIFIER_TOO_LONG; coluna += yyleng; return IDENTIFIER; }
0[xX][0-9a-fA-F]+       { coluna += yyleng;return NUM_HEXA; }
0[1-7][0-7]*            { coluna += yyleng; return NUM_OCTAL; }
^[0-9]+":"              {coluna += yyleng;}
[0-9]+                  { coluna += yyleng; return NUM_INTEGER; }
\'"\\a"\'               {return CHARACTER;}
\'"\\b"\'               {return CHARACTER;}
\'"\\f"\'               {return CHARACTER;}
\'"\\n"\'               {return CHARACTER;}
\'"\\r"\'               {return CHARACTER;}
\'"\\t"\'               {return CHARACTER;}
\'"\\v"\'               {return CHARACTER;}
\'"\\\\"\'              {return CHARACTER;}
\'"\\\'"\'              {return CHARACTER;}
\'"\\\""\'              {return CHARACTER;}
\'"\\?"\'               {return CHARACTER;}
\'"\\0"\'               {return CHARACTER;}
\'.\'                   {return CHARACTER;}
\"([^\\\"\n]|\\[abfnrtv\\\'\"?0])*\"       { coluna += yyleng; return STRING; }
"/*"                    {initLine = linha;initColunm = coluna; coluna += yyleng;BEGIN(COMMENT);}
"//".*\n                { coluna = 1; linha++; /* Ignora comentários de uma linha */ }
\n                      { coluna = 1; linha++; /* Ignora novas linhas */ }
[ ]+                    { coluna += yyleng; /* Ignora espaços em branco e tabulações */ }
.                       {return ERRO; }


<COMMENT>{
"*/"        {coluna += colunasComment + yyleng;linha += linhasComment;colunasComment = 0;linhasComment = 0; BEGIN(INITIAL); }
"/*/"       {coluna += colunasComment+ yyleng;linha += linhasComment;colunasComment = 0;linhasComment = 0; BEGIN(INITIAL); }
"/*"        {return WARNING;}
\n          {linhasComment++ ;colunasComment = 1; coluna = 0;}
" "         {colunasComment += yyleng;}
.           {colunasComment += yyleng; }
<<EOF>>     {coluna = initColunm;linha = initLine; BEGIN(INITIAL);return UNCLOSED_COMMENT;}
} 
%%
void printString(const char *text) {
    // Remove as aspas iniciais e finais e substitui \\" por \"
    const char *start = text + 1; // Remove a primeira aspas
    char buffer[1024]; // Buffer para armazenar a string processada
    char *ptr = buffer;
    
    while (*start != '\0' && *(start + 1) != '\0') {
        if (*start == '\\' && (*(start + 1) == '"' || *(start + 1) == '\\')) {
            *ptr++ = *start++;
        }
        *ptr++ = *start++; 
    }
    *ptr = '\0'; // Finaliza a string processada
    
    printf("STRING(%s)", buffer);
}

void printfChar(const char *text) {
    printf("CHARACTER(");
    int i = 0;
    char aux = text[i];
    while(aux != '\0'){
        i++;
        aux = text[i];
    }
    if(i == 3)printf("%c)",text[1]);
    else if(i == 4)printf("%c%c)", text[1], text[2]);
    
}

int main(int argc, char **argv)
{
    int tok;
    int firstToken = 1;
    while ((tok = yylex()) != 0) { // yylex() returns 0 at EOF
        if (firstToken) {
            firstToken = 0;
        } else {
            printf("\n");
        }
        if(tok == IDENTIFIER || tok == NUM_HEXA|| tok == NUM_INTEGER|| tok == NUM_OCTAL)printf("%s(%s)", getTokenName(tok), yytext);
        else if(tok == ERRO){
            printf("%s:lexical:%d:%d: %s", getTokenName(tok),linha,coluna, yytext);
            coluna += yyleng;
        }
        else if(tok == UNCLOSED_COMMENT)printf("%s:lexical:%d:%d: unterminated comment", getTokenName(tok),initLine,initColunm);
        else if(tok == IDENTIFIER_TOO_LONG)printf("%s:lexical:%d:%d: identifier too long", getTokenName(tok),linha,coluna);
        else if(tok == STRING)printString(yytext);
        else if(tok == CHARACTER)printfChar(yytext);
        else if(tok == WARNING){
            printf("warning:%d:%d: '/*' within block comment", linha+linhasComment,coluna+colunasComment);
            colunasComment += yyleng;
        }
        else printf("%s", getTokenName(tok));
    }
    return 0;
}