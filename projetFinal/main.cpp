#include <utility>
#include <string>
#include <iostream>
#include <memory>
#include "structures.h"
using namespace std;

std::vector<std::pair<int, int>> piece::trouverChemin(const std::pair<int, int> destination) {
	vector<pair<int, int>> chemin;
	// Un objet qui est simplement une pièce est une case vide, donc le déplacement est impossible, d'où un chemin vide
	return chemin;
}
bool piece::demanderMouvement(const std::pair<int, int> destination) {
	// Un objet qui est simplement une pièce est une case vide, donc aucun mouvement n'est possible
	cout << "La case est vide, il n'y a rien à deplacer" << endl;
	return false;
}
piece::piece(std::pair<int, int> maCase) {
	nature_ = "X"; // Une nature X signifie une case vide pour l'instant
	coordonnees_ = maCase;
}
piece::piece(string nature, std::string couleur, std::pair<int, int> maCase) {
	nature_ = nature;
	couleur_ = couleur;
	coordonnees_ = maCase;

}
void piece::afficher() {
	cout << nature_ << " "; // Affiche la nature de la piece
}
Echiquier::Echiquier() {
	// Quand on crée l'échiquier, on veut que les cases soient vides initialement 
	for (int i = 0; i < 8; i++) // Parcours les lignes de l'échiquier
	{
		for (int j = 0; j < 8; j++) // Parcours les colonnes de l'échiquier
		{
			pair<int, int> coordonneesPiece;
			coordonneesPiece.first = i;
			coordonneesPiece.second = j;
			tableau_[i][j] = make_unique<piece>(coordonneesPiece); // Instantiation d'une case vide aux bonnes coordonnees
		}
	}
}
void piece::afficherCoordonnees() {
	cout << coordonnees_.first << ',' << coordonnees_.second << endl;
 }
template <class TypePiece>
void Echiquier::modifierCase(const std::pair<int, int> coordonnees, const TypePiece& remplacement) {
	// L'usage du template TypePiece permet d'éviter l'object slicing 
	TypePiece nouvellePiece(remplacement.nature_, remplacement.couleur_, coordonnees);
	tableau_[coordonnees.first][coordonnees.second] = make_unique<TypePiece>(nouvellePiece);
}
void Echiquier::viderCase(const std::pair<int, int> coordonnees) {
	tableau_[coordonnees.first][coordonnees.second] = make_unique<piece>(coordonnees); // Pour vider une case, on place une nouvelle piece X dans le tableau à son endroit
}
void Echiquier::afficherEchiquier() {
	for (int i = 0; i < 8; i++) // Parcours les lignes de l'échiquier
	{
		for (int j = 0; j < 8; j++) // Parcours les colonnes de l'échiquier
		{
			tableau_[i][j].get()->afficher(); // Affiche la case
		}
		cout << '\n'; // 
	}
}
void Echiquier::deplacerPiece(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination) {
	// Demande à la pièce de vérifier si le mouvement demander est possible
	bool mouvementPossible = tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->demanderMouvement(coordonneesDestination);
	if (mouvementPossible)
	{
		// Si le mouvement est possible, on élabore le chemin à suivre en fonction de la pièce
		std::vector<std::pair<int, int>> chemin = tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->trouverChemin(coordonneesDestination);
		// On vérifie que le mouvement ne brise aucune règle de jeu
		bool mouvementLegal = verifierLegaliteMouvement(chemin, coordonneesDestination);
		if (mouvementLegal) {
			// Si le mouvement est légal, on modifie la case de destination et on vide la case de départ
			modifierCase(coordonneesDestination, *tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get());
			viderCase(coordonneesInitiales);
		}
	}
	else cout << "Mouvement impossible " << endl;
}

bool Echiquier::verifierLegaliteMouvement(const std::vector<std::pair<int, int>> chemin, const std::pair<int, int> destination) {
	int etapeChemin = 0;
	pair<int, int> prochaineCase = chemin[etapeChemin];
	do
	{	
		// Cette boucle Do While s'assure de la legalite du chemin en testant divers règles:
		prochaineCase = chemin[etapeChemin];
		// Note: On cherche la prochaine case au début de la boucle pour pouvoir effectuer des tests sur la case finale si besoin est
		// Si il y a une piece sur le chemin, autre que la case finale, le mouvement est illegal
		if (tableau_[prochaineCase.first][prochaineCase.second].get()->nature_ != "X" and prochaineCase != destination) {
			cout << "Il y a une pièce sur le chemin voulu autre que sur la case finale: Mouvement illegal!" << endl;
			return false;
		}
		etapeChemin++;
	} while (prochaineCase != destination); // Tant que la destination finale n'a pas été atteinte, on continue de suivre le chemin
	return true; // Si aucun des tests n'a échoué, le mouvement est jugé légal 
}

void Echiquier::afficherInfosCase(pair<int, int> coordonnees) {
	cout << "La case aux coordonnees: ";
	tableau_[coordonnees.first][coordonnees.second].get()->afficherCoordonnees();
	cout << "Est une " << tableau_[coordonnees.first][coordonnees.second].get()->nature_;

	cout << " de couleur " << tableau_[coordonnees.first][coordonnees.second].get()->couleur_;
}
int main() {
	string sepratation = " \n --------------------------------------------------------------- \n";
	cout << "Tableau initial" << endl;
	cout << '\n';
	Echiquier echiquier;
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	// Test d'un changement de case 
	pair<int, int> nouvelleCoordonnees, coordonneesInitiales;
	nouvelleCoordonnees.first = 0;
	coordonneesInitiales.first = 6;
	nouvelleCoordonnees.second = 0;
	coordonneesInitiales.second = 6;

	piece nouvellePiece("T", "noir", coordonneesInitiales);
	cout << "On demande la modification de la case (0,0) en une piece de nature T: " << endl;
	cout << '\n';
	echiquier.modifierCase(nouvelleCoordonnees, nouvellePiece);
	echiquier.afficherEchiquier();
	// Test: déplacer une case vide 
	
	nouvelleCoordonnees.first = 7;
	nouvelleCoordonnees.second = 7;
	cout << sepratation;
	cout << '\n';
	cout << "On demande le deplacement de la piece a la case (6,6), vers la case (7,7) :" << endl;
	cout << '\n';
	echiquier.deplacerPiece(coordonneesInitiales ,nouvelleCoordonnees);
	cout << sepratation;
	cout << '\n';
	// Test: Affichage d'une case pour vérifier qu'elle a les bonnes coordonnees, nature/couleur... 
	nouvelleCoordonnees.first = 0;
	nouvelleCoordonnees.second = 0;
	cout << "On demande l'affichage de la case aux coordonnees:\n" << nouvelleCoordonnees.first << ',' << nouvelleCoordonnees.second << endl;
	echiquier.afficherInfosCase(nouvelleCoordonnees);
	return 1;
}