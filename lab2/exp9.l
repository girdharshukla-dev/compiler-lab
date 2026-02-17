%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
%}

%option noyywrap

DIGIT [0-9]

ENDING_00  {DIGIT}*00
THREE_222  {DIGIT}*222{DIGIT}*

%%

^{ENDING_00}$ {
    printf("Token A (Ends in 00): %s\n", yytext);
}

{THREE_222} {
    printf("Token B (Contains 222): %s\n", yytext);
}

{DIGIT}+ {
    int i, len = yyleng, count;
    for (i = 0; i <= len - 5; i++) {
        count = 0;
        for (int j = i; j < i + 5; j++)
            if (yytext[j] == '5') count++;
        if (count < 2) {
            printf("Rejected (Violates 5-block rule): %s\n", yytext);
            return 0;
        }
    }
    printf("Token C (Valid 5-block rule): %s\n", yytext);
}

.|\n { }

%%

int main() {
    yylex();
    return 0;
}
