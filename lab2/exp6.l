%{
#include <stdio.h>
#include <stdlib.h>

FILE *out;
%}

%%
[ \t]+   { fputc(' ', out); }
\n       { fputc('\n', out); }
.                { fputc(yytext[0], out); }
%%

int main(int argc, char *argv[]) {

    FILE *in = fopen(argv[1], "r");

    out = fopen(argv[2], "w");

    yyin = in;
    yylex();

    fclose(in);
    fclose(out);
    return 0;
}

int yywrap() { return 1; }
