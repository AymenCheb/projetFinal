#include <utility>
#include <string>
#include <iostream>
#include <memory>
#include "structures.h"
using namespace std;

/**
* Programme qui implément un jeu d'échecs
* \file   main.cpp
* \author Chebbi Mohamed Aymen, Jaafar Hady, Panoyan Arthur
* \date   12 avril 2021
* Créé le 08 avril 2021
*/

// implémentations de la classe Piece 
//[
std::vector<std::pair<int, int>> piece::trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) {
	vector<pair<int, int>> chemin;
	// Un objet qui est simplement une pièce est une case vide, donc le déplacement est impossible, d'où un chemin vide
	return chemin;
}
bool piece::demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) {
	// Un objet qui est simplement une pièce est une case vide, donc aucun mouvement n'est possible
	cout << "La case est vide, il n'y a rien a deplacer" << endl;
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


//Constructeurs des differentes pieces
//[
//Constructeur des tours
Tour::Tour(string nature, string couleur) : piece(nature, couleur) {
}
//Constructeur des cavaliers
Cavalier::Cavalier(string nature, string couleur) : piece(nature, couleur) {
}
//Constructeur des Rois
Roi::Roi(string nature, string couleur) : piece(nature, couleur) {
}
//]


//Constructeur de l'echiquier
Echiquier::Echiquier() {
	// Quand on crée l'échiquier, on veut que les cases soient vides initialement 
	for (int i = 0; i < 8; i++) // Parcours les lignes de l'échiquier
	{
		for (int j = 0; j < 8; j++) // Parcours les colonnes de l'échiquier
		{
			tableau_[i][j] = make_shared<piece>(); // Instantiation d'une case vide aux bonnes coordonnees
		}
	}
}


//Differentes methodes de la classe Echiquier
//[
//Cette methode permet de modifier une case precise de l'echiquier, en passant en parametre les coordonnees de la case, ainsi que la piece que l'on souhaite placer a cette case
template <class TypePiece>
void Echiquier::modifierCase(const std::pair<int, int> coordonnees, const shared_ptr<TypePiece>* remplacement) {
	// L'usage du template TypePiece permet d'éviter l'object slicing 
	tableau_[coordonnees.first][coordonnees.second] = *remplacement;
}

//Cette methode permet de vider une case, en y inserant une Piece ( directement de la classe Piece, cette Piece n'est ni une tour, ni un fou etc..)
void Echiquier::viderCase(const std::pair<int, int> coordonnees) {
	tableau_[coordonnees.first][coordonnees.second] = make_shared<piece>(); // Pour vider une case, on place une nouvelle piece X dans le tableau à son endroit
}
//Methode pour afficher l'echiquier dans le terminal
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

// Methode permettant de deplacer une piece, on donne en parametres les coordonnees initiales de la piece ainsi que les coordonnees de destination
void Echiquier::deplacerPiece(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination) {
	// Demande à la pièce de vérifier si le mouvement demander est possible
	bool mouvementPossible = tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->demanderMouvement(coordonneesInitiales, coordonneesDestination);
	if (mouvementPossible)
	{
		// Si le mouvement est possible, on élabore le chemin à suivre en fonction de la pièce
		std::vector<std::pair<int, int>> chemin = tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->trouverChemin(coordonneesInitiales, coordonneesDestination);
		// On vérifie que le mouvement ne brise aucune règle de jeu
		bool mouvementLegal = verifierLegaliteMouvement(chemin, coordonneesDestination, tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->couleur_);
		if (mouvementLegal) {
			// Si le mouvement est légal, on modifie la case de destination et on vide la case de départ
			modifierCase(coordonneesDestination, &tableau_[coordonneesInitiales.first][coordonneesInitiales.second]);
			viderCase(coordonneesInitiales);
		}
	}
	else cout << "Mouvement impossible " << endl;
}

/*Methode permettant de verifier la legallite d'un mouvement : ce n'est pas cette methode qui verifie les regles de deplacement specifiques a chaque pieces,
cette methode verifie plutot des regles plus generales, comme par exemple si une piece alliee se trouve sur la case sur laquelle on souhaite se deplacer etc*/
bool Echiquier::verifierLegaliteMouvement(const std::vector<std::pair<int, int>> chemin, const std::pair<int, int> destination, string couleurPiece) {
	int etapeChemin = 0;
	pair<int, int> prochaineCase = chemin[etapeChemin];
	do
	{	
		// Cette boucle Do While s'assure de la legalite du chemin en testant divers règles:
		prochaineCase = chemin[etapeChemin];
		// Note: On cherche la prochaine case au début de la boucle pour pouvoir effectuer des tests sur la case finale si besoin est
		// Si il y a une piece sur le chemin, autre que la case finale, le mouvement est illegal
		if (tableau_[prochaineCase.first][prochaineCase.second].get()->nature_ != "X" and prochaineCase != destination) {
			cout << "Il y a une piece sur le chemin voulu autre que sur la case finale: Mouvement illegal!" << endl;
			return false;
		}
		else if (prochaineCase == destination and tableau_[prochaineCase.first][prochaineCase.second].get()->couleur_ == couleurPiece) {
			cout << "La destiantion contient une piece de la meme couleur: Mouvement illegal!" << endl;
			return false;
		}
		etapeChemin++;
	} while (prochaineCase != destination); // Tant que la destination finale n'a pas été atteinte, on continue de suivre le chemin
	return true; // Si aucun des tests n'a échoué, le mouvement est jugé légal 
}

//Methode qui permet d'afficher les informations d'une case precise, on passe en parametre les coordonnees de la case
void Echiquier::afficherInfosCase(pair<int, int> coordonnees) {
	cout << "La case aux coordonnees: " << coordonnees.first << ',' << coordonnees.second << endl;
	cout << "Est une " << tableau_[coordonnees.first][coordonnees.second].get()->nature_;

	cout << " de couleur " << tableau_[coordonnees.first][coordonnees.second].get()->couleur_;
}//]


//[
/*Implementation des methodes demanderMouvement specifiques a chaque piece : cette methode retourne, en fonction de la piece, true si cette piece
peut se deplacer de la maniere dont on souhaite le faire, ou false si le deplacement demander brise les regles de deplacement de cette piece*/

bool Tour::demanderMouvement(const std::pair<int, int> depart, const pair<int, int> destination) {
	//La tour se deplace soit horizontalement, soit verticalement, de ce fait , si ses coordonnees de depart sont (x,y), alors a l'arrivee, aux coordonnees (w,z)
	//si le mouvement est legal, on aura alors x = w ou y = z
	if (destination.first != depart.first && destination.second != depart.second) {
		return false;
	}
	else
		return true;
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

bool Roi::demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) {
	/*Le roi peut se deplacer uniquement d'une cases dans toute les direction. Si il part de (x,y) et arrive a (w,z)
	alors,  |x-w| > 1 ou si |y-z| > 1, cela signifie que le roi ne s'est pas deplacer uniquement d'une case,
	et son mouvement est donc illegal*/
	int differenceX = depart.first - destination.first;
	int differenceY = depart.second - destination.second;
	if (abs(differenceX) > 1 || abs(differenceY) > 1)		//Roi peut seulement bouger de 1 cases a la fois
		return false;
	else
		return true;
}
//]

//[
/*Implementation des methodes trouverChemin specifiques a chaque piece, cette methode retourne un vector contenant
les coordonnees des differentes cases par lesquelles une piece doit passer pour se rendre de sa case initiale jusqu'a celle
a laquelle on souahite la deplacer*/

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

std::vector<std::pair<int, int>> Cavalier::trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) {
	//Le chemin du deplacement d'un cavalier est uniquement sa case d'arrivee, car il passe directement de sa case de depart a sa case d'arrivee.
	vector<pair<int, int>> chemin;
	chemin.push_back(destination);
	return chemin;
}

std::vector<std::pair<int, int>> Roi::trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) {
	//Le roi se deplace uniquement d'une case, son chemin de deplacement est donc uniquement composer de sa case d'arrivee
	vector<pair<int, int>> chemin;
	chemin.push_back(destination);
	return chemin;
}
//]


int main() {
	string sepratation = " \n --------------------------------------------------------------- \n";
	cout << "Tableau initial" << endl;
	cout << '\n';
	Echiquier echiquier;
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	pair<int, int> nouvelleCoordonnees, coordonneesInitiales;
	// Test: déplacer une case vide 
	nouvelleCoordonnees.first = 7;
	nouvelleCoordonnees.second = 7;
	cout << sepratation;
	cout << '\n';
	cout << "On demande le deplacement de la piece a la case (6,6), vers la case (7,7) :" << endl;
	cout << '\n';
	echiquier.deplacerPiece(coordonneesInitiales, nouvelleCoordonnees);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Coordonnees pour tester des deplacmeents de pieces
	nouvelleCoordonnees.first = 3;
	coordonneesInitiales.first = 5;
	nouvelleCoordonnees.second = 4;
	coordonneesInitiales.second = 4;

	// Creation d'une tour et test de deplacements
	//Creation de la tour et positionnement de la tour aux coordonnees
	Tour nouvellePiece("T", "noir");
	shared_ptr<Tour> pointeurTour = make_shared<Tour>(nouvellePiece);
	cout << "On demande la modification de la case (5,4) en une tour: " << endl;
	cout << '\n';
	echiquier.modifierCase(coordonneesInitiales, &pointeurTour);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement legal de la tour
	cout << "On deplace la tour de 2 cases vers le haut" << endl;
	echiquier.deplacerPiece(coordonneesInitiales, nouvelleCoordonnees);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement illegal de la tour
	cout << "On tente de deplacer la tour en diagonale" << endl;
	pair<int, int> coordonneesTest(2, 3);
	echiquier.deplacerPiece(nouvelleCoordonnees, coordonneesTest);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';


	//Creation d'un cavalier et test de deplacements
	//Creation du cavalier et positionnement
	Cavalier premierCavalier("C", "noir");
	shared_ptr<Cavalier> pointeurCavalier = make_shared<Cavalier>(premierCavalier);
	pair<int, int> coordonneesCavalier(5, 4);
	echiquier.modifierCase(coordonneesCavalier, &pointeurCavalier);
	cout << "On positionne un cavalier aux coordonnees (5,4)" << endl;
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement legal du cavalier
	pair<int, int> deplacementCavalier(3, 3);
	echiquier.deplacerPiece(coordonneesCavalier, deplacementCavalier);
	cout << "On deplace le cavaleir aux coordonnees (3,3)" << endl;
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacment illegal du cavalier
	pair<int, int> deplacementIllegalCavalier(2, 2);
	cout << "On essaie de deplacer le cavalier a la position (2,2)" << endl;
	echiquier.deplacerPiece(deplacementCavalier, deplacementIllegalCavalier);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	


	//Creation d'un roi et test de deplacements
	//Creation du roi et positionnement
	Roi premierRoi("R", "noir");
	shared_ptr<Roi> pointeurRoi = make_shared<Roi>(premierRoi);
	pair<int, int> coordonneesRoi(2, 4);
	echiquier.modifierCase(coordonneesRoi, &pointeurRoi);
	cout << "On positionne le Roi aux coordonnees(2,4)" << endl;
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement legal du Roi
	pair<int, int> deplacementRoi(2, 5);
	echiquier.deplacerPiece(coordonneesRoi, deplacementRoi);
	cout << "On deplace le Roi aux coordonnees (2,5)" << endl;
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement illegal du roi
	pair<int, int> deplacementIllegalRoi(4, 6);
	cout << "On essaie de deplacer le Roi aux coordonnees (3,6), donc de deux cases." << endl;
	cout << '\n';
	echiquier.deplacerPiece(deplacementRoi, deplacementIllegalRoi);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';


	//Test pour deplacer une piece sur une case contenant une autre piece d'une meme couleur
	pair<int, int> deplacementRoiMange(3, 4);
	cout << "On essaie de deplacer le Roi aux coordonnees(3, 4), ou une piece alliee se trouve" << endl;
	cout << '\n';
	echiquier.deplacerPiece(deplacementRoi, deplacementRoiMange);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';


	//Test deplacer une tour alors q'une piece se trouve sur son chemin
	cout << "On essaie de deplacer la Tour des coordonnees (3,4) aux coordonnees (3,2), alors qu'un cavalier allie se trouve aux coordonnees (3,3)" << endl;
	nouvelleCoordonnees.first = 3;
	nouvelleCoordonnees.second = 4;
	pair<int, int> coordonneesDeplacementTour(3, 2);
	echiquier.deplacerPiece(nouvelleCoordonnees, coordonneesDeplacementTour);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';

	// Test: Affichage d'une case pour vérifier qu'elle a les bonnes coordonnees, nature/couleur... 
	nouvelleCoordonnees.first = 3;
	nouvelleCoordonnees.second = 4;
	cout << "On demande l'affichage de la case aux coordonnees:\n" << nouvelleCoordonnees.first << ',' << nouvelleCoordonnees.second << endl;
	echiquier.afficherInfosCase(nouvelleCoordonnees);
	cout << sepratation;
	cout << '\n';
	return 1;
}