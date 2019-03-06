2_uzduotis: funkcijos.o in_out.o tikrinimas.o vector.o list.o deque.o
	g++ -o 2_uzduotis 2_uzduotis.cpp funkcijos.o in_out.o tikrinimas.o vector.o list.o deque.o
funkcijos:
	g++ -std=c++11 funkcijos.cpp
in_out:
	g++ -std=c++11 in_out.cpp
tikrinimas:
	g++ -std=c++11 tikrinimas.cpp
vector:
	g++ -std=c++11 vector.cpp
list:
	g++ -std=c++11 list.cpp	
deque:
	g++ -std=c++11 deque.cpp	
clean:
	del *.o 2_uzduotis.exe
