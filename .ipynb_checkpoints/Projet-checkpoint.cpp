#include "coord.hpp"
#include "grille.hpp"
#include "termite.hpp"
#include "jeu.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include <iostream>
#include <array>
#include <vector>
using namespace std;


int main(int argc, const char **argv){
	Grille x;
	vector<Termite>colonie1 = initialiseGrille(x); // on crée notre colonie et on choisit aleatoirement le contenu de chaque case ;
	Jeu z = Jeu{colonie1, x};
	z.simulation();
	return 0;
}
