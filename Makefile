all: search

run: compile
	./search < data/level-0/cross

time: compile
	time ./search < data/level-0/cross

compile: search

search: main.cpp
	g++ -O3 -o search main.cpp
