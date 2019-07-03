all: ag_tests

ag_tests: ag.o tree.o ag_tests.cpp
	g++ -std=c++17 -o ag_tests ag_tests.cpp tree.o ag.o

tree.o: tree.h tree.cpp
	g++ -std=c++17 -c tree.cpp

ag.o: attr.h ag.h ag.cpp
	g++ -std=c++17 -c ag.cpp
