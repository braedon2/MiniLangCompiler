
CC = gcc -g

all: lex.yy.o y.tab.o tree.o main.o
	$(CC) -o minic -lfl lex.yy.o y.tab.o tree.o main.o

lex.yy.c: mini.l y.tab.h
	flex mini.l

y.tab.h y.tab.c: mini.y
	bison -t --yacc --defines mini.y

y.tab.o: y.tab.h y.tab.c
	$(CC) -c y.tab.c

lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c

tree.o: tree.c tree.h
	$(CC) -c tree.c

main.o: main.c
	$(CC) -c main.c

clean:
	rm lex.yy.c y.tab.c *.o
