#include <iostream>
#include "doctest.h"
#include "coord.hpp"
using namespace std;


Coord::Coord(int x, int y): lig{x}, col{y} {
	if( lig >= tailleGrille or col >= tailleGrille or lig < 0 or col < 0){
		throw invalid_argument("les coordonnées ne sont pas dans la grille");
	}
}

int Coord::getLig() const{
	return lig;
}

TEST_CASE("Test récuperer une ligne"){
    //construire un constructeur pour une coordonnée pour faire appel a la methode getLig
    Coord c = {5,4};
    CHECK(c.getLig()==5);
}
int Coord::getCol() const{
	return col;
}

TEST_CASE("Test récuperer une colonne"){
    //construire un constructeur pour une coordonnée pour faire appel a la methode getCol
    Coord c = {5,4};
    CHECK(c.getCol()==4);
}

ostream& operator<<(ostream& out, Coord c){
	out<<'('<<c.getLig()<<','<<c.getCol()<<')'<<endl;
	return out;
}

bool operator==(Coord a, Coord b) {
	return (a.getLig() == b.getLig() and  a.getCol() == b.getCol());
}


ostream& operator<<(ostream& out, Direction c){
	switch(c){
		case Direction::nord_ouest : out<<"nord_ouest"<<endl; break;
		case Direction::sud_ouest : out<<"sud_ouest"<<endl; break;
		case Direction::ouest : out<<"ouest"<<endl; break;
		case Direction::nord_est : out<<"nord_est"<<endl; break;
		case Direction::sud_est : out<<"sud_est"<<endl; break;
		case Direction::est : out<<"est"<<endl; break;
		case Direction::sud : out<<"sud_ouest"<<endl; break;
		case Direction::nord : out<<"nord"<<endl; break;
	}
	return out;
}

Direction aDroite(Direction d){
	return Direction((int(d)+1)%8);
}

Direction aGauche(Direction d){
	return Direction((int(d)-1)%8);
}

TEST_CASE("Test des fonctions aGauche et aDroite"){
Direction dir = Direction::nord;
for (int i = 0; i < 8; i++) {
    cout << dir << " -> " << aGauche(dir) << " -> " << aDroite(aGauche(dir)) << endl;
    dir = aDroite(dir);
}
}

Coord devantCoord(Coord c, Direction d){
	Coord e = c;
	try{
		switch(d){
			case Direction::nord_ouest : e = Coord{c.getLig()-1, c.getCol()-1}; break;
			case Direction::sud_ouest : e = Coord{c.getLig()+1, c.getCol()-1}; break;
			case Direction::ouest : e = Coord{c.getLig(), c.getCol()-1}; break;
			case Direction::nord_est : e = Coord{c.getLig()-1, c.getCol()+1}; break;
			case Direction::sud_est : e = Coord{c.getLig()+1, c.getCol()+1}; break;
			case Direction::est : e = Coord{c.getLig(), c.getCol()+1}; break;
			case Direction::sud : e = Coord{c.getLig()+1, c.getCol()}; break;
			case Direction::nord : e = Coord{c.getLig()-1, c.getCol()}; break;
		}
	}catch(exception const& e){}
	return e;
}

TEST_CASE("Test devantCoord()") {
    Coord c1(2, 2); // coordonnées au centre de la grille
    CHECK(devantCoord(c1, Direction::nord) == Coord(2, 1));
    CHECK(devantCoord(c1, Direction::nord_est) == Coord(3, 1));
    CHECK(devantCoord(c1, Direction::est) == Coord(3, 2));
    CHECK(devantCoord(c1, Direction::sud_est) == Coord(3, 3));
    CHECK(devantCoord(c1, Direction::sud) == Coord(2, 3));
    CHECK(devantCoord(c1, Direction::sud_ouest) == Coord(1, 3));
    CHECK(devantCoord(c1, Direction::ouest) == Coord(1, 2));
    CHECK(devantCoord(c1, Direction::nord_ouest) == Coord(1, 1));

    Coord c2(0, 2); // coordonnées sur le bord gauche de la grille
    CHECK_THROWS_AS(devantCoord(c2, Direction::ouest), invalid_argument);
    CHECK_THROWS_AS(devantCoord(c2, Direction::nord_ouest) , invalid_argument);
    CHECK(devantCoord(c2, Direction::nord) == Coord(0, 1));
    CHECK(devantCoord(c2, Direction::nord_est) == Coord(1, 1));
    CHECK(devantCoord(c2, Direction::est) == Coord(1, 2));
    CHECK(devantCoord(c2, Direction::sud_est) == Coord(1, 3));
    CHECK(devantCoord(c2, Direction::sud) == Coord(0, 3));
    CHECK_THROWS_AS(devantCoord(c2, Direction::sud_ouest), invalid_argument);

    Coord c3(2, 0); // coordonnées sur le bord supérieur de la grille
    CHECK_THROWS_AS(devantCoord(c3, Direction::nord), invalid_argument);
    CHECK_THROWS_AS(devantCoord(c3, Direction::nord_est) , invalid_argument);
    CHECK(devantCoord(c3, Direction::est) == Coord(3, 0));
    CHECK(devantCoord(c3, Direction::sud_est) == Coord(3, 1));
    CHECK(devantCoord(c3, Direction::sud) == Coord(2, 1));
    CHECK(devantCoord(c3, Direction::sud_ouest) == Coord(1, 1));
}