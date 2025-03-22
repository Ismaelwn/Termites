#ifndef coord_HPP
#define coord_HP
#include <iostream>
using namespace std;

const int tailleGrille = 20;

enum class Direction{nord_ouest, nord, nord_est,
est, sud_est, sud, sud_ouest, ouest};

Direction aGauche(Direction d);
Direction aDroite(Direction d);

class Coord{
	public:
	//operations d'accès
	int getLig() const;
	int getCol() const;
	//constructeurs
	Coord(int x, int y);
	//operateurs de test
	
	//autres
	private:
	int lig;
	int col;
};

Coord devantCoord(Direction d, Coord c);
ostream& operator<<(ostream& out, Coord c);
bool operator==(Coord a, Coord b);

#endif