#include <utility>
#include <string>
#include <iostream>
#include <memory>
#include "structures.h"
using namespace std;

piece::piece() {
	nature_ = "X";
}
piece::piece(string nature) {
	nature_ = nature;
}
void piece::afficherNature() {
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
			tableau_[i][j].get()->afficherNature();
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
	// Test d'un changement de case 
	pair<int, int> nouvelleCoordonnees;
	nouvelleCoordonnees.first = 0;
	nouvelleCoordonnees.second = 0;
	piece nouvellePiece("T");
	echiquier.modifierCase(nouvelleCoordonnees, nouvellePiece);
	echiquier.afficherEchiquier();
	return 1;
}