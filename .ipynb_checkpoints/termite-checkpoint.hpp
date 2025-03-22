#ifndef termite_HPP
#define termite_HP
#include <iostream>
#include <array>
#include <vector>

class Termite{
	private:
	int idT;
	Coord xy;
	Direction direction;
	bool brindille;
	int sablier; //nombre de deplacements
	bool TourneSurPlace;
	public:
	Termite(int idT, Coord c);
	string toString() const;
	Direction directionTermite();
	Coord devant() const;
	bool porteBrindille();
	Coord Getcoord() const; //moi
	
	void tourneADroite();
	void tourneAGauche();
	void tourneAleat();
	
	bool laVoieEstLibre(const Grille &g) const; //renvoie si la case devant le termite est libre
	bool brindilleEnFace(const Grille &g) const; //renvoie si la case devant le termite contient une brindille
	int voisinsLibre(const Grille &g); //renvoie le nombre de cases libre autour du termite
	void avance(Grille &g); //avance le termite
	void marcheAleatoire(Grille &g); //déplace aléatoirement le termite
	void chargeBrindille(Grille &g); //le termite prend une brindille
	void dechargeBrindille(Grille &g); //le termite pose une brindille
	
	//OUBLIE PAS EN DESSOUS 
	void vieTermite(Grille &g); //algorithme du termite

};

const float probaTourner = 0.1; // 10%
const int dureeSablier = 6;




#endif