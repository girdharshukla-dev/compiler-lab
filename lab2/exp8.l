%{
#include <stdio.h>
%}

/* Definitions */
LETTER      [a-zA-Z]
DIGIT       [0-9]
ID          {LETTER}({LETTER}|{DIGIT})*
NUMBER      {DIGIT}+

%%

"if"        { printf("KEYWORD(IF)\n"); }
"else"      { printf("KEYWORD(ELSE)\n"); }
"while"     { printf("KEYWORD(WHILE)\n"); }

{ID}        { printf("IDENTIFIER(%s)\n", yytext); }
{NUMBER}    { printf("INTEGER(%s)\n", yytext); }

"+"         { printf("PLUS\n"); }
"-"         { printf("MINUS\n"); }
"*"         { printf("MULTIPLY\n"); }
"/"         { printf("DIVIDE\n"); }

[ \t\n]+    ;   /* ignore whitespace */

.           { printf("INVALID(%s)\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
