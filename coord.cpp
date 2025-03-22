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

int Coord::getCol() const{
	return col;
}

ostream& operator<<(ostream& out, Coord c){
	out<<'('<<c.getLig()<<','<<c.getCol()<<')'<<endl;
	return out;
}

bool operator==(Coord a, Coord b) {
	return (a.getLig() == b.getLig() and  a.getCol() == b.getCol());
}

TEST_CASE("test operator == "){
	Coord a = Coord{1,0};
	Coord b = Coord{0,0};
	Coord c = Coord{1,1};
	CHECK(a == Coord{1, 0});
	CHECK_FALSE( a == b );
	CHECK_FALSE( a == c );
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
    int val = int(d) - 1;
    if(val < 0){
        val += 8;
    }
    return Direction(val);
}

TEST_CASE("Test des fonctions aGauche et aDroite"){
	Direction dir = Direction::nord;
	for (int i = 0; i < 8; i++) {
		cout << dir << " -> " << aGauche(dir) << " -> " << aDroite(aGauche(dir)) << endl;
		dir = aDroite(dir);
    }
	CHECK( dir == Direction::nord );
	
}
Coord devantCoord(Direction d, Coord c){
	try{
	Coord e = c;
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
		return e;
	}catch (const std::exception& e) {
		return c;
	}
		
	
}


TEST_CASE("Test devantCoord()") {
    Coord c1(2, 2); // coordonnées au centre de la grille
    CHECK(devantCoord(Direction::nord, c1) == Coord(1, 2));
    CHECK(devantCoord(Direction::nord_est, c1) == Coord(1, 3));
    CHECK(devantCoord(Direction::est, c1) == Coord(2,3));
    CHECK(devantCoord(Direction::sud_est, c1 ) == Coord(3, 3));
    CHECK(devantCoord(Direction::sud, c1) == Coord(3,2));
    CHECK(devantCoord(Direction::sud_ouest, c1) == Coord(3,1));
    CHECK(devantCoord(Direction::ouest, c1) == Coord(2,1));
    CHECK(devantCoord(Direction::nord_ouest, c1) == Coord(1, 1));

    Coord c2(0, 2); // coordonnées sur le bord gauche de la grille
    CHECK(devantCoord(Direction::nord_ouest, c2) == c2);
    CHECK(devantCoord(Direction::nord, c2) == c2);
    CHECK(devantCoord(Direction::nord_est, c2) == c2);
    CHECK(devantCoord(Direction::est, c2) == Coord(0, 3));
    CHECK(devantCoord(Direction::sud_est, c2) == Coord(1, 3));
    CHECK(devantCoord(Direction::sud, c2) == Coord(1, 2));
    CHECK(devantCoord(Direction::sud_ouest, c2) == Coord(1, 1));
	CHECK(devantCoord(Direction::ouest, c2) == Coord(0, 1));

    Coord c3(2, 0); // coordonnées sur le bord supérieur de la grille
    CHECK(devantCoord(Direction::nord, c3) == Coord{1, 0} );
    CHECK(devantCoord(Direction::nord_est, c3) == Coord{1,1} );
    CHECK(devantCoord(Direction::est, c3) == Coord(2, 1));
    CHECK(devantCoord(Direction::sud_est, c3) == Coord(3, 1));
    CHECK(devantCoord(Direction::sud, c3) == Coord{3, 0});
    CHECK(devantCoord(Direction::sud_ouest, c3) == c3);

}
