g++ -c Valeur.cpp -o Valeur.o && g++ -c Valeur.cpp -o Valeur.o && bison -d --report=state  -o syntsem.c syntsem.y && flex -o lexical.c lexical.lex && gcc -o syntsem syntsem.c lexical.c
