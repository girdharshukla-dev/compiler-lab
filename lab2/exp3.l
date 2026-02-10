%{
#include <stdio.h>
#include <stdlib.h>

FILE *out;
%}

%%
[ \t]+      { fputc(' ', out); }     /* collapse spaces and tabs */
\n          { fputc('\n', out); }    /* preserve newlines */
.           { fputc(yytext[0], out); }
%%

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s input.txt output.txt\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        perror("Input file");
        return 1;
    }

    out = fopen(argv[2], "w");
    if (!out) {
        perror("Output file");
        return 1;
    }

    yyin = in;
    yylex();

    fclose(in);
    fclose(out);
    return 0;
}

int yywrap() {
    return 1;
}
