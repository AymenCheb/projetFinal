#include <utility>
#include <string>
#include <iostream>
#include <memory>
#include "structures.h"
using namespace std;

std::pair<int, int>* piece::trouverChemin(const std::pair<int, int> destination) {
	std::pair<int, int> retour;
	retour.first = 0;
	retour.second = 0;
	return &retour;
}
bool piece::demanderMouvement(const std::pair<int, int> destination) {
	cout << "La case est vide, il n'y a rien à deplacer" << endl;
	return false;
}
piece::piece() {
	nature_ = "X";
}
piece::piece(string nature) {
	nature_ = nature;
}
void piece::afficher() {
	cout << nature_ << " ";
}
Echiquier::Echiquier() {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			piece pieceCourante("X");
			tableau_[i][j] = make_unique<piece>();
		}
		cout << '\n';
	}
}
void Echiquier::modifierCase(const std::pair<int, int> coordonnees, const piece remplacement) {
	tableau_[coordonnees.first][coordonnees.second] = make_unique<piece>(remplacement);
}
void Echiquier::viderCase(const std::pair<int, int> coordonnees) {
	tableau_[coordonnees.first][coordonnees.second] = make_unique<piece>();
}
void Echiquier::afficherEchiquier() {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			tableau_[i][j].get()->afficher();
		}
		cout << '\n';
	}
}
void Echiquier::deplacerPiece(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination) {
	bool mouvementPossible = tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->demanderMouvement(coordonneesDestination);
	if (mouvementPossible)
	{
		std::pair<int, int>* chemin = tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->trouverChemin(coordonneesDestination);
		/*bool mouvementLegal = verifierLegaliteMouvement(chemin);
		if (mouvementLegal) {
			modifierCase(coordonneesDestination, *tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get());
			viderCase(coordonneesInitiales);
		}*/
	}
	else cout << "Mouvement impossible " << endl;
}
int main() {
	string sepratation = " \n --------------------------------------------------------------- \n";
	cout << "Tableau initial" << endl;
	Echiquier echiquier;
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	// Test d'un changement de case 
	pair<int, int> nouvelleCoordonnees, coordonneesInitiales;
	nouvelleCoordonnees.first = 0;
	coordonneesInitiales.first = 7;
	nouvelleCoordonnees.second = 0;
	coordonneesInitiales.second = 7;

	piece nouvellePiece("T");
	cout << "On demande la modification de la case (0,0) en une piece de nature T: " << endl;
	cout << '\n';
	echiquier.modifierCase(nouvelleCoordonnees, nouvellePiece);
	echiquier.afficherEchiquier();
	// Test: déplacer une case vide 
	
	nouvelleCoordonnees.first = 8;
	nouvelleCoordonnees.second = 8;
	cout << sepratation;
	cout << '\n';
	cout << "On demande le deplacement de la piece a la case (7,7), vers la case (8,8) :" << endl;
	echiquier.deplacerPiece(coordonneesInitiales ,nouvelleCoordonnees);
	return 1;
}