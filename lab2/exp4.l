%{
#include <stdio.h>
%}

/* ----- Definitions ----- */
digit       [0-9]
letter      [a-zA-Z]
id          {letter}({letter}|{digit})*
int         {digit}+
float       {digit}*(\.{digit}+)?

%%

"int"       { printf("KEYWORD: %s\n", yytext); }
"float"     { printf("KEYWORD: %s\n", yytext); }
"if"        { printf("KEYWORD: %s\n", yytext); }
"else"      { printf("KEYWORD: %s\n", yytext); }
"return"    { printf("KEYWORD: %s\n", yytext); }

{id}        { printf("IDENTIFIER: %s\n", yytext); }

{int}    { printf("INT: %s\n", yytext); }

{float}  {printf("FLOAT: %s\n", yytext); }

"+"|"-"|"*"|"/"|"="|"=="|"!="|"<"|">"|"<="|">=" { printf("OPERATOR: %s\n", yytext); }

";"|","|"("|")"|"{"|"}" { printf("SEPARATOR: %s\n", yytext); }

[ \t\n]+    ;

.           { printf("UNKNOWN: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() { return 1; }
