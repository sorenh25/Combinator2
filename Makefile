main: Combinator.o main.cpp
	g++ -Wall main.cpp Combinator.o -std=gnu++11 -static-libstdc++ -o Combinator-teamSorenHolm

Combinator.o: Combinator.cpp Combinator.hpp
	g++ Combinator.cpp -Wall -c -std=gnu++11 -static-libstdc++

runI: main
	Combinator-teamSorenHolm testFiles/I.txt

runK: main
	Combinator-teamSorenHolm testFiles/K.txt

runS: main
	Combinator-teamSorenHolm testFiles/S.txt

runC: main
	Combinator-teamSorenHolm testFiles/complex.txt

runB: main
	Combinator-teamSorenHolm boolean.txt

runBO: main
	Combinator-teamSorenHolm bonus.txt
