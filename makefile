all : main

main : main.c hash.c
	gcc -g -o $@ $^

clean :
	rm -rf main *core*