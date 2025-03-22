#include "coord.hpp"
#include "grille.hpp"

#include <iostream>
#include "doctest.h"
using namespace std;


Case::Case():valeur{-1}, occupe{false}{
};

void Grille::poseBrindille(Coord c){
	if(grille[c.getLig()][c.getCol()].occupe) {
		throw invalid_argument("on ne peut pas poser de brindille dans cette case");
	}
	grille[c.getLig()][c.getCol()].valeur = -1;
	grille[c.getLig()][c.getCol()].occupe = true;
}

array<array<Case,tailleGrille>,tailleGrille> Grille::getGrille() const{ // moi qui l'ai rajouté
	return grille;
}
		
void Grille::enleveBrindille(Coord c){
	if(grille[c.getLig()][c.getCol()].valeur == -1 and grille[c.getLig()][c.getCol()].occupe ){
		grille[c.getLig()][c.getCol()].occupe = false;
	}else{
		throw invalid_argument("on ne peut pas retirer de brindille dans cette case si il n'y en a pas");
	}
}
	
bool Grille::contientBrindille(Coord c) const{
	return (grille[c.getLig()][c.getCol()].valeur == -1 and grille[c.getLig()][c.getCol()].occupe);
}

void Grille::poseTermite(Coord c, int idT){
	if(not(grille[c.getLig()][c.getCol()].occupe)){
		grille[c.getLig()][c.getCol()].valeur = idT;
		grille[c.getLig()][c.getCol()].occupe = true;
	}else{
		throw invalid_argument("on ne peut pas poser de termites a un endroit non vide");
	}
}
	
void Grille::enleveTermite(Coord c){
	if(grille[c.getLig()][c.getCol()].valeur != -1 and grille[c.getLig()][c.getCol()].occupe == true){
		grille[c.getLig()][c.getCol()].valeur = -1;
		grille[c.getLig()][c.getCol()].occupe = false;
	}else{
		throw invalid_argument("on ne peut pas retirer de termite dans cette case si il n'y en a pas");
	}	
}
	
int Grille::numeroTermite(Coord c) const{
	if(grille[c.getLig()][c.getCol()].valeur == -1){
		throw invalid_argument("il n'y a pas de termites a cet endroit");
	}
	return grille[c.getLig()][c.getCol()].valeur;
}

bool Grille::estVide(Coord c) const{ //changement 05/05/2023
	if(grille[c.getLig()][c.getCol()].occupe){
		return false;
	}else{
		return true;
	}
}


void Grille::afficheJeu(){
	for(int x = 0; x < tailleGrille; x++){
		for(int y = 0; y < tailleGrille; y++){
			if( y == 0 ){
				cout<<"|";
			}
			if( grille[x][y].occupe == true and grille[x][y].valeur == -1){
				cout<<"*";
				}else if(grille[x][y].occupe == true and grille[x][y].valeur != -1){
				cout<<"T";
			}else if(grille[x][y].occupe == false and grille[x][y].valeur == -1){
				cout<<" ";
			}
			
		}
	}
}

TEST_CASE("Test de l'initialisation de la grille"){
	Grille test;
	for(int x = 0; x < tailleGrille; x++){ //initialisation reussit
		for(int y = 0; y < tailleGrille; y++){
			CHECK(test.estVide(Coord{x,y}));
		}
	}
}

				
	
TEST_CASE("Test du depot ou du fait de retirer une brindille"){
	Grille test;
	CHECK(test.estVide(Coord{0,0}));
	test.poseBrindille(Coord{0,0});
	CHECK_FALSE(test.estVide(Coord{0,0}));
	CHECK( test.contientBrindille(Coord{0,0}) );
	test.enleveBrindille(Coord{0,0});
	CHECK_FALSE(test.contientBrindille(Coord{0,0}));
	CHECK(test.estVide(Coord{0,0}));
	test.poseBrindille(Coord{0,0});
	CHECK_THROWS_AS(test.poseBrindille(Coord{0,0}), invalid_argument);
	test.enleveBrindille(Coord{0,0});
	test.poseTermite(Coord{0,0}, 0);
	CHECK_THROWS_AS(test.poseBrindille(Coord{0,0}), invalid_argument);
}

TEST_CASE("Test du depot ou du fait de retirer un termite"){
	Grille test;
	CHECK(test.estVide(Coord{0,0}));
	test.poseTermite(Coord{0,0}, 0);
	CHECK_FALSE(test.estVide(Coord{0,0}));
	CHECK_THROWS_AS(test.poseTermite(Coord{0,0}, 1), invalid_argument);
	test.enleveTermite(Coord{0,0});
	CHECK(test.estVide(Coord{0,0}));
}