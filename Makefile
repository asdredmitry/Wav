main.o : main.cpp 
	g++ -c main.cpp -o main.o
wav.o : wav.cpp wav.hpp
	g++ -c wav.cpp -o wav.o
main : main.o wav.o 
	g++ main.o wav.o -o main
clean : 
	rm -rf main.o wav.o mian