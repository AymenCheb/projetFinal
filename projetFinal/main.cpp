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
void piece::demanderMouvement(const std::pair<int, int> destination) {
	cout << "La case est vide, il n'y a rien à déplacer";
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

int main() {
	string sepratation = " \n --------------------------------------------------------------- \n";
	cout << "Tableau initial" << endl;
	Echiquier echiquier;
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	// Test d'un changement de case 
	pair<int, int> nouvelleCoordonnees;
	nouvelleCoordonnees.first = 0;
	nouvelleCoordonnees.second = 0;
	piece nouvellePiece("T");
	echiquier.modifierCase(nouvelleCoordonnees, nouvellePiece);
	echiquier.afficherEchiquier();
	return 1;
}