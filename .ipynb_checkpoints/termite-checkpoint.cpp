#include "coord.hpp"
#include "grille.hpp"
#include "termite.hpp"
#include "doctest.h"
#include <iostream>
using namespace std;


Termite::Termite(int idt, Coord c): idT{idt}, xy{c}, direction{Direction::nord}, brindille{false}, sablier{0}, TourneSurPlace{false}{}

Coord Termite::Getcoord() const{
	return Coord{xy.getLig(),xy.getCol()};
}
string Termite::toString() const{
	string rtr;
	switch(direction){
		case Direction::nord : case Direction::sud :rtr = "|"; break;
	    case Direction::nord_ouest : case Direction::sud_est : rtr = "\\" ; break;
		case Direction::sud_ouest : case Direction::nord_est : rtr =  "/"; break;
		case Direction::ouest : case Direction::est : rtr = "-"; break;
			}
	return rtr;
}

Direction Termite::directionTermite(){
	return direction;
}

Coord Termite::devant() const{
	return devantCoord(direction, xy);// je l'ai deja defini autant l'utiliser 
}

bool Termite::porteBrindille() const{
	return brindille;
}

void Termite::tourneADroite(){
	direction = aDroite(direction);//je l'ai deja defini 
}
void Termite::tourneAGauche(){
	direction = aGauche(direction);
}

TEST_CASE(" Test des fonctions precedentes "){
	Termite x1 = Termite{ 0, Coord{0, 0} };
	x1.tourneADroite();
	CHECK(x1.directionTermite() == Direction::nord_est );
	x1.tourneAGauche();
	CHECK(x1.directionTermite() == Direction::nord );
	CHECK_FALSE(x1.directionTermite() == Direction::sud );
	CHECK(x1.toString() == "|");
	x1.tourneAGauche();
	CHECK(x1.toString() == "\\" );
	
}

void Termite::tourneAleat(){
	float random = (rand()%100)/100.00; // pour que ce soit vraiment 50/50
	if( random > 0.50){
		tourneADroite();
	}else{
		tourneAGauche();
	}
}

bool Termite::laVoieEstLibre(const Grille &g) const{
	return (g.estVide(devant()));
	}


TEST_CASE(" Test des fonctions precedentes "){
	Grille test;
	Termite x1 = Termite{0, Coord{0, 0}};
	Termite x2 = Termite{1, Coord{tailleGrille-1,tailleGrille-1}};
	test.poseTermite(x1.Getcoord(), 0);
	test.poseTermite(x2.Getcoord(), 1);
	CHECK_FALSE(x1.laVoieEstLibre(test) );
	CHECK(x2.laVoieEstLibre(test) );
}


bool Termite::brindilleEnFace(const Grille &g) const{
	return (g.contientBrindille(devant()));
}

int Termite::voisinsLibre(const Grille &g){ // j'aurai voulu rajouter un const car je ne souhaite pas modifier un attribut de la structure mais je ne souhaitais pas rajouter des elements compliqués pour traiter une copy de la termite sur laquelle on applique la methode
	int cpt = 0;
	for(int i = 0; i < 8; i++ ){
	tourneADroite();
	if(laVoieEstLibre(g)){
		cpt++;
	}
	}
	return cpt;
}

TEST_CASE(" Test des fonctions precedentes " ){
	Grille test;
	Termite x1 = Termite{0, Coord{(tailleGrille-1)/2, tailleGrille-1}};
	Termite x2 = Termite{1, Coord{(tailleGrille-1)/2,(tailleGrille-1)/2}};
	Termite x3 = Termite{2, Coord{(tailleGrille-1),(tailleGrille-1)}};
	Termite x4 = Termite{3, Coord{(tailleGrille-1),(tailleGrille-1)/2}};
	test.poseTermite(x1.Getcoord(), 0);
	test.poseTermite(x2.Getcoord(), 1);
	test.poseTermite(x3.Getcoord(), 2);
	test.poseTermite(x4.Getcoord(), 3);
	CHECK(x3.voisinsLibre(test) == 3 );
	CHECK(x2.voisinsLibre(test) == 8 );
	CHECK(x1.voisinsLibre(test) == 5 );
	CHECK(x4.voisinsLibre(test) == 5 );
}

void Termite::avance(Grille &g){
	if(laVoieEstLibre(g)){
		g.enleveTermite(xy);
		xy = devant();
		g.poseTermite(xy, idT);
		sablier++;
		}
}


TEST_CASE(" Test des fonctions precedentes " ){
	Grille test;
	Termite x1 = Termite{0, Coord{0, 0}};
	
	test.poseTermite(x1.Getcoord(), 0);
	
	x1.avance(test);
	cout<<x1.Getcoord()<<endl;
	x1.tourneADroite();
	x1.avance(test);
	cout<<x1.Getcoord()<<endl;
	x1.tourneADroite();
	x1.avance(test);
	cout<<x1.Getcoord()<<endl;
	x1.tourneADroite();
	x1.avance(test);
	cout<<x1.Getcoord()<<endl;
	x1.tourneADroite();
	x1.avance(test);
	cout<<x1.Getcoord()<<endl;
	x1.tourneADroite();
	x1.avance(test);
	cout<<x1.Getcoord()<<endl;
	x1.tourneADroite();
	x1.avance(test);
	cout<<x1.Getcoord()<<endl;
}

void Termite::marcheAleatoire(Grille &g){
	float hasard = (rand()%101)/100.00;
	if( laVoieEstLibre(g) ){
		if( hasard <= probaTourner){
			tourneAleat();
	
		}else{
			avance(g);
		}
	}else{
		tourneAleat();
	}
}


TEST_CASE("Test de la fonction precedente"){
	Grille x;
	Termite z = Termite{0, Coord{0, 0} };
	x.poseTermite( z.Getcoord(), 0); 
	CHECK(z.directionTermite() == Direction::nord);
	z.tourneADroite();
	CHECK(z.directionTermite() != Direction::nord);
	z.tourneAleat();
	CHECK(z.directionTermite()!= Direction::nord_est);
}

void Termite::chargeBrindille(Grille &g){
	if(brindilleEnFace(g) and not(porteBrindille()) and sablier >= dureeSablier){
		brindille = true;
		g.enleveBrindille(devant());
		sablier = 0;
	}
}

void Termite::dechargeBrindille(Grille &g){
	if(sablier >= dureeSablier and laVoieEstLibre(g) and porteBrindille()/* and voisinsLibre(g) > 1*/){ // pour pas qu'il s'enferme tout seul
		brindille = false;
		g.poseBrindille(devant());
		//sablier -= dureeSablier;
		sablier = 0;
	}
}
		
		

void Termite::vieTermite(Grille &g){

	if(not(porteBrindille())){
	chargeBrindille(g);
	}
	if(porteBrindille()){
	dechargeBrindille(g);
	}
	marcheAleatoire(g);
	
}

	
	
	
	
	
	