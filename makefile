all: main
main: main.c
	gсс -Wall -Werror main.c -o main
run:
	./main
