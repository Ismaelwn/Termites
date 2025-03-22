all = Projet

Projet: Projet.o coord.o grille.o termite.o jeu.o
	g++ -o Projet Projet.o coord.o grille.o termite.o jeu.o
	
Projet.o: Projet.cpp jeu.hpp termite.hpp grille.hpp coord.hpp
	g++ -std=c++11 -Wall -c Projet.cpp

coord.o: coord.cpp coord.hpp
	g++ -std=c++11 -Wall -c coord.cpp

grille.o: grille.cpp grille.hpp coord.hpp
	g++ -std=c++11 -Wall -c grille.cpp
	
termite.o: termite.cpp termite.hpp grille.hpp coord.hpp
	g++ -std=c++11 -Wall -c termite.cpp
	
jeu.o : jeu.cpp jeu.hpp termite.hpp grille.hpp coord.hpp
	g++ -std=c++11 -Wall -c jeu.cpp

tests : test.o coord.o grille.o grille.o termite.o
	g++ -o tests coord.o grille.o termite.o test.o

test.o: test.cpp jeu.hpp termite.hpp grille.hpp coord.hpp
	g++ -std=c++11 -Wall -c test.cpp


check : tests
	./tests

clean :
	rm -f *.o tests