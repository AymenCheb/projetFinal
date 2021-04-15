#include <string>
#include <iostream>
#include <vector>
#include "Cavalier.h"

using namespace std;

//Constructeur des cavaliers
Cavalier::Cavalier(string nature, string couleur) : piece(nature, couleur) {
}

bool Cavalier::demanderMouvement(const std::pair<int, int> depart, const pair<int, int> destination) {
	/*Le cavalier se deplace en L. De ce fait, si il se deplace de 2 cases vers le haut ou le bas, il doit se deplacer d'une case vers la gauche ou vers la droite
	De la meme maniere, s'il se deplace de 2 cases vers la gauche ou vers la droite, il doit se deplacer d'une case vers le haut ou vers le bas
	Tout autre mouvement est illegal*/
	int differenceX = depart.first - destination.first;
	int differenceY = depart.second - destination.second;
	if (differenceX == -2 || differenceX == 2) {
		if (differenceY == -1 || differenceY == 1)
			return true;
		else
			return false;
	}
	if (differenceY == -2 || differenceY == 2) {
		if (differenceX == -1 || differenceX == 1)
			return true;
		else
			return false;
	}
	return false;
}

std::vector<std::pair<int, int>> Cavalier::trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) {
	//Le chemin du deplacement d'un cavalier est uniquement sa case d'arrivee, car il passe directement de sa case de depart a sa case d'arrivee.
	vector<pair<int, int>> chemin;
	chemin.push_back(destination);
	return chemin;
}