#include <string>
#include <iostream>
#include <vector>
#include "Piece.h"
#include "Tour.h"
using namespace std;

//Constructeur des tours
Tour::Tour(string nature, string couleur) : piece(nature, couleur) {
}

bool Tour::demanderMouvement(const std::pair<int, int> depart, const pair<int, int> destination) {
	//La tour se deplace soit horizontalement, soit verticalement, de ce fait , si ses coordonnees de depart sont (x,y), alors a l'arrivee, aux coordonnees (w,z)
	//si le mouvement est legal, on aura alors x = w ou y = z
	if (destination.first != depart.first && destination.second != depart.second) {
		return false;
	}
	else
		return true;
}

vector<pair<int, int>> Tour::trouverChemin(const std::pair<int, int> depart, pair<int, int> destination) {
	vector<pair<int, int>> chemin;
	if (depart.first != destination.first) {   //Si la tour se deplace verticalement
		if (depart.first > destination.first) {  // Si la tour se deplace vers le haut 
			for (int i = depart.first - 1; i >= destination.first; i--) { // A chaque iteration, on rajoute les coordonnees de la case par laquelle la tour passe, en incluant la case d'arrivee, et en excluant la case de depart
				pair<int, int> etape(i, depart.second);
				chemin.push_back(etape);
			}
		}
		else //Si la tour se depalce vers le bas
		{
			for (int i = depart.first + 1; i <= destination.first; i++)// A chaque iteration, on rajoute les coordonnees de la case par laquelle la tour passe, en incluant la case d'arrivee, et en excluant la case de depart
			{
				pair<int, int> etape(i, depart.second);
				chemin.push_back(etape);
			}
		}
	}
	else // Si la tour se deplace horizontalement
	{
		if (depart.second > destination.second) { // Si la tour se depalce vers la gauche 
			for (int i = depart.second - 1; i >= destination.second; i--)// A chaque iteration, on rajoute les coordonnees de la case par laquelle la tour passe, en incluant la case d'arrivee, et en excluant la case de depart
			{
				pair<int, int> etape(depart.first, i);
				chemin.push_back(etape);
			}
		}
		else //Si la tour se depalce vers la droite
		{
			for (int i = depart.second + 1; i <= destination.second; i++)// A chaque iteration, on rajoute les coordonnees de la case par laquelle la tour passe, en incluant la case d'arrivee, et en excluant la case de depart
			{
				pair<int, int> etape(depart.first, i);
				chemin.push_back(etape);
			}
		}
	}
	return chemin;
}