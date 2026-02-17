filename=$1

echo "flex \"$filename\""
flex "$filename"

echo "gcc lex.yy.c -o main"
gcc lex.yy.c -o main
