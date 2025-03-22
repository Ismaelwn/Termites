#ifndef jeu_HPP
#define jeu_HP
#include <iostream>
#include <array>
#include <vector>
using namespace std;

class Jeu{
	private:
	vector<Termite>colonie1;
	Grille terrain;
	public:
	Jeu(vector<Termite>colonie1, Grille terrain);
	void coherence() const;
	void afficheJeu() const;
	void simulation();
};

//vector<Termite> creeColonie(Grille &c); //new
vector<Termite> initialiseGrille(Grille& x);



#endif
	