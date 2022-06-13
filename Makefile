
base64test : main.o base64.o
	gcc main.o base64.o -o base64test

main.o : main.c
	gcc -c main.c -o main.o

base64.o : base64.c
	gcc -c base64.c -o base64.o