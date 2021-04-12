#include <utility>
#include <string>
#include <iostream>
#include <memory>
#include "structures.h"
using namespace std;


// impl�mentations de la classe Piece 
//[
std::vector<std::pair<int, int>> piece::trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) {
	vector<pair<int, int>> chemin;
	// Un objet qui est simplement une pi�ce est une case vide, donc le d�placement est impossible, d'o� un chemin vide
	return chemin;
}
bool piece::demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) {
	// Un objet qui est simplement une pi�ce est une case vide, donc aucun mouvement n'est possible
	cout << "La case est vide, il n'y a rien � deplacer" << endl;
	return false;
}
piece::piece() {
	nature_ = "X"; // Une nature X signifie une case vide pour l'instant
	couleur_ = "aucune";
}
piece::piece(string nature, std::string couleur) {
	nature_ = nature;
	couleur_ = couleur;

}

void piece::afficher() {
	cout << nature_ << " "; // Affiche la nature de la piece
}
//]
//Constructeur des tours
Tour::Tour(string nature, string couleur) : piece(nature, couleur) {
}
//Constructeur des cavaliers
Cavalier::Cavalier(string nature, string couleur) : piece(nature, couleur) {
}
//Constructeur des Rois
Roi::Roi(string nature, string couleur) : piece(nature, couleur) {
}

Echiquier::Echiquier() {
	// Quand on cr�e l'�chiquier, on veut que les cases soient vides initialement 
	for (int i = 0; i < 8; i++) // Parcours les lignes de l'�chiquier
	{
		for (int j = 0; j < 8; j++) // Parcours les colonnes de l'�chiquier
		{
			tableau_[i][j] = make_shared<piece>(); // Instantiation d'une case vide aux bonnes coordonnees
		}
	}
}

template <class TypePiece>
void Echiquier::modifierCase(const std::pair<int, int> coordonnees, const shared_ptr<TypePiece>* remplacement) {
	// L'usage du template TypePiece permet d'�viter l'object slicing 
	tableau_[coordonnees.first][coordonnees.second] = *remplacement;
}
void Echiquier::viderCase(const std::pair<int, int> coordonnees) {
	tableau_[coordonnees.first][coordonnees.second] = make_shared<piece>(); // Pour vider une case, on place une nouvelle piece X dans le tableau � son endroit
}
void Echiquier::afficherEchiquier() {
	for (int i = 0; i < 8; i++) // Parcours les lignes de l'�chiquier
	{
		for (int j = 0; j < 8; j++) // Parcours les colonnes de l'�chiquier
		{
			tableau_[i][j].get()->afficher(); // Affiche la case
		}
		cout << '\n'; // 
	}
}
void Echiquier::deplacerPiece(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination) {
	// Demande � la pi�ce de v�rifier si le mouvement demander est possible
	bool mouvementPossible = tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->demanderMouvement(coordonneesInitiales, coordonneesDestination);
	if (mouvementPossible)
	{
		// Si le mouvement est possible, on �labore le chemin � suivre en fonction de la pi�ce
		std::vector<std::pair<int, int>> chemin = tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->trouverChemin(coordonneesInitiales, coordonneesDestination);
		// On v�rifie que le mouvement ne brise aucune r�gle de jeu
		bool mouvementLegal = verifierLegaliteMouvement(chemin, coordonneesDestination, tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->couleur_);
		if (mouvementLegal) {
			// Si le mouvement est l�gal, on modifie la case de destination et on vide la case de d�part
			modifierCase(coordonneesDestination, &tableau_[coordonneesInitiales.first][coordonneesInitiales.second]);
			viderCase(coordonneesInitiales);
		}
	}
	else cout << "Mouvement impossible " << endl;
}

bool Echiquier::verifierLegaliteMouvement(const std::vector<std::pair<int, int>> chemin, const std::pair<int, int> destination, string couleurPiece) {
	int etapeChemin = 0;
	pair<int, int> prochaineCase = chemin[etapeChemin];
	do
	{	
		// Cette boucle Do While s'assure de la legalite du chemin en testant divers r�gles:
		prochaineCase = chemin[etapeChemin];
		// Note: On cherche la prochaine case au d�but de la boucle pour pouvoir effectuer des tests sur la case finale si besoin est
		// Si il y a une piece sur le chemin, autre que la case finale, le mouvement est illegal
		if (tableau_[prochaineCase.first][prochaineCase.second].get()->nature_ != "X" and prochaineCase != destination) {
			cout << "Il y a une pi�ce sur le chemin voulu autre que sur la case finale: Mouvement illegal!" << endl;
			return false;
		}
		else if (prochaineCase == destination and tableau_[prochaineCase.first][prochaineCase.second].get()->couleur_ == couleurPiece) {
			cout << "La destiantion contient une piece de la m�me couleur: Mouvement illegal!" << endl;
			return false;
		}
		etapeChemin++;
	} while (prochaineCase != destination); // Tant que la destination finale n'a pas �t� atteinte, on continue de suivre le chemin
	return true; // Si aucun des tests n'a �chou�, le mouvement est jug� l�gal 
}

void Echiquier::afficherInfosCase(pair<int, int> coordonnees) {
	cout << "La case aux coordonnees: " << coordonnees.first << ',' << coordonnees.second << endl;
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
	nouvelleCoordonnees.first = 3;
	coordonneesInitiales.first = 5;
	nouvelleCoordonnees.second = 4;
	coordonneesInitiales.second = 4;
	// Creation d'une tour et test de deplacements
	Tour nouvellePiece("T", "noir");
	shared_ptr<Tour> pointeurTour = make_shared<Tour>(nouvellePiece);
	cout << "On demande la modification de la case (5,4) en une tour: " << endl;
	cout << '\n';
	echiquier.modifierCase(coordonneesInitiales, &pointeurTour);
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	cout << "On deplace la tour de 2 cases vers le haut" << endl;
	echiquier.deplacerPiece(coordonneesInitiales, nouvelleCoordonnees);
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	cout << "On tente de deplacer la tour en diagonale" << endl;
	pair<int, int> coordonneesTest(2, 3);
	echiquier.deplacerPiece(nouvelleCoordonnees, coordonneesTest);
	// Test: d�placer une case vide 
	nouvelleCoordonnees.first = 7;
	nouvelleCoordonnees.second = 7;
	cout << sepratation;
	cout << '\n';
	cout << "On demande le deplacement de la piece a la case (6,6), vers la case (7,7) :" << endl;
	cout << '\n';
	echiquier.deplacerPiece(coordonneesInitiales ,nouvelleCoordonnees);
	cout << sepratation;
	cout << '\n';
	// Test: Affichage d'une case pour v�rifier qu'elle a les bonnes coordonnees, nature/couleur... 
	nouvelleCoordonnees.first = 0;
	nouvelleCoordonnees.second = 0;
	cout << "On demande l'affichage de la case aux coordonnees:\n" << nouvelleCoordonnees.first << ',' << nouvelleCoordonnees.second << endl;
	echiquier.afficherInfosCase(nouvelleCoordonnees);
	cout << sepratation;
	cout << '\n';
	//Test du cavalier
	Cavalier premierCavalier("C", "noir");
	shared_ptr<Cavalier> pointeurCavalier = make_shared<Cavalier>(premierCavalier);
	pair<int, int> coordonneesCavalier(5, 4);
	echiquier.modifierCase(coordonneesCavalier, &pointeurCavalier);
	cout << "On positionne un cavalier aux coordonnees (5,4)" << endl;
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement legal du cavalier
	pair<int, int> deplacementCavalier(3, 3);
	echiquier.deplacerPiece(coordonneesCavalier, deplacementCavalier);
	cout << "On deplace le cavaleir aux coordonnees (3,3)" << endl;
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacment illegal du cavalier
	pair<int, int> deplacementIllegalCavalier(2, 2);
	cout << "On essaie de deplacer le cavalier a la position (2,2)" << endl;
	echiquier.deplacerPiece(deplacementCavalier, deplacementIllegalCavalier);
	
	//Test du roi
	Roi premierRoi("R", "noir");
	shared_ptr<Roi> pointeurRoi = make_shared<Roi>(premierRoi);
	pair<int, int> coordonneesRoi(2, 4);
	echiquier.modifierCase(coordonneesRoi, &pointeurRoi);
	cout << "On positionne le Roi aux coordonnees(2,4)" << endl;
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement du Roi
	pair<int, int> deplacementRoi(2, 5);
	echiquier.deplacerPiece(coordonneesRoi, deplacementRoi);
	cout << "On deplace le Roi aux coordonnees (2,5)" << endl;
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << '\n';
	//Test verifier longueur de deplacement
	pair<int, int> deplacementIllegalRoi(4, 6);
	cout << "On essaie de deplacer le Roi aux coordonnees (3,6), donc de deux cases." << endl;
	cout << '\n';
	echiquier.deplacerPiece(deplacementRoi, deplacementIllegalRoi);
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Test verifier si il mange une piece ami
	pair<int, int> deplacementRoiMange(3, 4);
	cout << "On essaie de deplacer le Roi aux coordonnees(3, 4), o� une piece ami se trouve" << endl;
	cout << '\n';
	echiquier.deplacerPiece(deplacementRoi, deplacementRoiMange);
	echiquier.afficherEchiquier();
	cout << '\n';
	
	return 1;
}