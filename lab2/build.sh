filename=$1
flex "$filename"
gcc lex.yy.c -o main