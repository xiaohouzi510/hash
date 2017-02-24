all : main

main : main.cpp hash.cpp
	g++ -g -o $@ $^

clean :
	rm -rf main *core*