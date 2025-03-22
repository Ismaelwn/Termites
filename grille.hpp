#ifndef grille_HPP
#define grille_HP
#include <iostream>
#include <array>


using namespace std;

struct Case{
	public:
	int valeur;
	bool occupe;
	//constructeurs
	Case();
};

class Grille{
	private:
	array<array<Case,tailleGrille>,tailleGrille>grille;
	public:
	void poseBrindille(Coord c);
	void enleveBrindille(Coord c);
	bool contientBrindille(Coord c) const;
	void poseTermite(Coord c, int idT);
	void enleveTermite(Coord c);
	int numeroTermite(Coord c) const;
	bool estVide(Coord c) const;
	void afficheJeu();
	array<array<Case,tailleGrille>,tailleGrille> getGrille() const; //moi
};

const float densiteBrindille=0.05;
const int nbTermites=2;

#endif