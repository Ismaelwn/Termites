#include "coord.hpp"
#include "grille.hpp"
#include "termite.hpp"
#include "jeu.hpp"

#include <iostream>
#include "doctest.h"
using namespace std;

Jeu::Jeu(vector<Termite>colonie, Grille terrain1): colonie1{colonie}, terrain{terrain1}{};

void Jeu::afficheJeu() const{
	array<array<Case,tailleGrille>,tailleGrille> Grille = terrain.getGrille();
	for(int x = 0; x < tailleGrille; x++){
		for(int y = 0; y < tailleGrille; y++){
			if(Grille[x][y].occupe == true and Grille[x][y].valeur != -1 ){
				if(colonie1[Grille[x][y].valeur].porteBrindille()){
					cout<<"\033[31;1m"<<colonie1[Grille[x][y].valeur].toString()<< "\033[0m" ;
				}else{
					cout<<"\033[37m"<<colonie1[Grille[x][y].valeur].toString()<< "\033[0m" ;
				}
			}else if(Grille[x][y].occupe == true and Grille[x][y].valeur == -1){
				cout<<"\033[32;5m"<<"*"<< "\033[0m" ;
			}else if(Grille[x][y].occupe == false and Grille[x][y].valeur == -1){
				cout<<" ";
			}
			
		}
	cout<<endl;
	}
}

vector<Termite> initialiseGrille(Grille& x) {
	srand((int)time(0));
    vector<Termite> termites;
    int rand_x, rand_y;
	float rand_br;
	//Pour initialiser les termites sur la grille et dans le vecteur
	for (int i = 0; i < nbTermites; i++) {
        // Réinitialiser les coordonnées aléatoires
        rand_x = rand() % tailleGrille;
        rand_y = rand() % tailleGrille;
		// Chercher une case vide sur la grille
        while (not(x.estVide(Coord{rand_x, rand_y}))) {
            rand_x = rand() % tailleGrille;
            rand_y = rand() % tailleGrille;
		}
		// Poser la termite sur la grille
        x.poseTermite(Coord{rand_x, rand_y}, i);
		// Ajouter la termite au vecteur
        termites.push_back(Termite{i, Coord{rand_x, rand_y}});
    }
	
	//Pour initialiser les brindilles 
	for( int i = 0; i < tailleGrille; i++){
		for( int y = 0; y < tailleGrille; y++){
			rand_br = (rand()%101)/100.00;
			if(rand_br <= densiteBrindille and x.estVide(Coord{i,y})){
				x.poseBrindille(Coord{i,y});
			}
		}
	}
			return termites;
}

void Jeu::coherence() const{
	//Cohérence termite-grille
	for( auto e : colonie1 ){
		if(terrain.getGrille()[e.Getcoord().getLig()][e.Getcoord().getCol()].occupe and terrain.getGrille()[e.Getcoord().getLig()][e.Getcoord().getCol()].valeur == -1){
			throw logic_error("il n'y a pas de termite a cet endroit");
		}else if(not(terrain.getGrille()[e.Getcoord().getLig()][e.Getcoord().getCol()].occupe) and terrain.getGrille()[e.Getcoord().getLig()][e.Getcoord().getCol()].valeur == -1){
			throw logic_error("il n'y a pas de termite a cet endroit");
		}
	}
	
	//Cohérence grille-termite
	for(int x = 0; x < tailleGrille; x++){
		for(int y = 0; y < tailleGrille; y++){
			if(terrain.getGrille()[x][y].valeur != -1){
				if( terrain.getGrille()[x][y].valeur >= nbTermites){
					throw logic_error("un termite inexistant dans la colonie est présent sur la grille");
				}else if( not( colonie1[terrain.getGrille()[x][y].valeur].Getcoord() == Coord{x, y}) ){
					throw logic_error("un termite dans la colonie n'est pas enregistré au bon endroit sur la grille");
				}
			}
	}
	}
	//coherence indice termite
	for( int i = 0; i < colonie1.size(); i++){
		if(terrain.getGrille()[colonie1[i].Getcoord().getLig()][colonie1[i].Getcoord().getCol()].valeur != i ){
		   throw logic_error("l'attribut idT pour une termite n'est pas bon");
		}
	}
}


	
void Jeu::simulation(){
	int nbpass = 10000;
	string choixOp;
	string action;
	int compteur;
	compteur = 0;
	cout<<"TOUR "<<compteur<<endl;
	cout<<" Voici votre grille initiale "<<endl;
	afficheJeu();
	do{
		cout<<" Souhaitez vous changer le nombre de passes ?"<<endl;
		cout<<" il est actuellement à "<<nbpass<<endl;
		cin >> choixOp;
		if( choixOp == "*" ){
			nbpass = nbpass*2;
		}
		if( choixOp == "/" ){
			nbpass = nbpass/2;
		}
		if( nbpass == 0 ){ //pour l'empecher de proposer une passe vide 
			nbpass = 1;
		}
		for(int x = 0; x < nbpass; x++){
			for(int i = 0; i < nbTermites; i++){
				colonie1[i].vieTermite(terrain);
			}
			compteur++;
		}
		cout<<"TOUR "<<compteur<<endl;
		afficheJeu();
		coherence();
		cout<<"on continue la simulation ?"<<endl;
		cin >> action;
		}while(action != "." );
	}

