%{
#include <stdio.h>

int line_count = 0;
int char_count = 0;
%}

%%
\n              { line_count++; char_count++; }
.               { char_count++; }
%%

int main() {
    yylex();
    printf("Lines: %d\n", line_count);
    printf("Characters: %d\n", char_count);
    return 0;
}

int yywrap() {
    return 1;
}
