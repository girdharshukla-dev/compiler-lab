%{
    #include <stdio.h>
%}

float [0-9]*(\.[0-9]+)
int   [0-9]+

%%
{float} {printf("FLOAT: %s\n", yytext);}
{int}   {printf("INT: %s\n", yytext);}
[ \t\n] ;
%%

int main(void){
    yylex();
    return 0;
}

int yywrap(){ return 1; }
