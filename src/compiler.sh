bison -d -o syntsem.c syntsem.y && flex -o lexical.c lexical.lex && gcc -o syntsem syntsem.c lexical.c
