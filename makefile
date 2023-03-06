all: main
main: main.c
	gсс -Wall -Werror -o myprog myprog.c
run:
	./main
