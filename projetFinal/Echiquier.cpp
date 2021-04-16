#pragma once
#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "Piece.h"
#include "Equipe.h"
#include "Roi.h"
#include "Cavalier.h"
#include "Tour.h"
#include "Echiquier.h"

using namespace std;


//Constructeur de l'echiquier
Echiquier::Echiquier(Equipe equipe1, Equipe equipe2) {
	// Quand on cr�e l'�chiquier, on veut que les cases soient vides initialement 
	equipes_[0] = equipe1;
	equipes_[1] = equipe2;
	for (int i = 0; i < 8; i++) // Parcours les lignes de l'�chiquier
	{
		for (int j = 0; j < 8; j++) // Parcours les colonnes de l'�chiquier
		{
			tableau_[i][j] = make_shared<piece>(); // Instantiation d'une case vide aux bonnes coordonnees
		}
	}
}

// Cette fonction retourne un int pour indiquer � quelle �quipe appartient une piece 
int Echiquier::determinerEquipe(std::pair<int, int> coordonnees) {
	if (equipes_[0].verifierPresenceMembre(coordonnees))
		return 0;
	if (equipes_[1].verifierPresenceMembre(coordonnees))
		return 1;
	else return 2;
};
// Cette fonction attribu correctement une equipe a une case en fonction de sa couleur
void Echiquier::attribuerEquipe(std::pair<int, int> coordonnes) {
	string couleurPiece = tableau_[coordonnes.first][coordonnes.second].get()->couleur_;
	if (couleurPiece == equipes_[0].couleur_)
		equipes_[0].ajouterMembre(coordonnes);
	else if (couleurPiece == equipes_[1].couleur_)
		equipes_[1].ajouterMembre(coordonnes);
	else cout << "La case n'a pas la meme couleur d'une des equipes" << endl;
}
bool Echiquier::verifierEchec(pair<int, int> positionRoi) {
	// Ajouter des tests pour v�rifier que l'on passe bien un roi 
	int indexEquipe = determinerEquipe(positionRoi);
	// Ce switch s'occupe de retirer la case de l'�quipe qui lui correspond
	switch (indexEquipe)
	{
	case 0:
		for (int i = 0; i < equipes_[1].nMembres_; i++)
		{
			if (validerMouvement(equipes_[1].listeDesCasesMembres_[i], positionRoi))
				return true;
		}
		break;
	case 1:
		for (int i = 0; i < equipes_[0].nMembres_; i++)
		{
			if (validerMouvement(equipes_[0].listeDesCasesMembres_[i], positionRoi))
				return true;
		}
		break;
	case 2: // Si la piece n'est dans aucune equipe, on peut juste passer
		break;
	}
	return false;
}



//Cette methode permet de vider une case, en y inserant une Piece ( directement de la classe Piece, cette Piece n'est ni une tour, ni un fou etc..)
void Echiquier::viderCase(const std::pair<int, int> coordonnees) {
	int indexEquipe = determinerEquipe(coordonnees);
	// Ce switch s'occupe de retirer la case de l'�quipe qui lui correspond
	switch (indexEquipe)
	{
	case 0:
	case 1:
		equipes_[indexEquipe].retirerMembre(coordonnees);
		break;
	case 2: // Si la piece n'est dans aucune equipe, on peut juste passer
		break;
	}
	tableau_[coordonnees.first][coordonnees.second] = make_shared<piece>(); // Pour vider une case, on place une nouvelle piece X dans le tableau � son endroit
}
//Methode pour afficher l'echiquier dans le terminal
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
void Echiquier::afficherMembresEquipe(string nom) {
	if (equipes_[0].nom_ == nom)
	{
		for (int i = 0; i < equipes_[0].nMembres_; i++) {
			pair<int, int> coordonneesMembre = equipes_[0].listeDesCasesMembres_[i];
			afficherInfosCase(coordonneesMembre);
		}
	}
}
bool Echiquier::validerMouvement(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination) {
	// Demande � la pi�ce de v�rifier si le mouvement demander est possible
	bool mouvementPossible = tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->demanderMouvement(coordonneesInitiales, coordonneesDestination);
	if (mouvementPossible)
	{
		// Si le mouvement est possible, on �labore le chemin � suivre en fonction de la pi�ce
		std::vector<std::pair<int, int>> chemin = tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->trouverChemin(coordonneesInitiales, coordonneesDestination);
		// On v�rifie que le mouvement ne brise aucune r�gle de jeu
		bool mouvementLegal = verifierLegaliteMouvement(chemin, coordonneesDestination, tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->couleur_);
		return mouvementLegal;
	}
	return false;
}


// Methode permettant de deplacer une piece, on donne en parametres les coordonnees initiales de la piece ainsi que les coordonnees de destination
void Echiquier::deplacerPiece(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination) {
	// On m�morise les pointeurs des pieces aux cases de d�part et de destination
	afficherInfosCase(coordonneesDestination);
	memoriserPieceDepart(&tableau_[coordonneesInitiales.first][coordonneesInitiales.second]);
	memoriserPieceDestination(&tableau_[coordonneesDestination.first][coordonneesDestination.second]);

	// Dans un premier temps, on v�rifie que la pi�ce a le droit d'effectuer ce mouvement
	if (validerMouvement(coordonneesInitiales, coordonneesDestination)) {
		// Si le mouvement est l�gal, on modifie la case de destination et on vide la case de d�part
		modifierCase(coordonneesDestination, &tableau_[coordonneesInitiales.first][coordonneesInitiales.second]);
		viderCase(coordonneesInitiales);
		// Dans un deuxi�me temps, on v�rifie si ce d�placement a mis le roi de la pi�ce en �chec
		if (verifierEchec(trouverPiece("R", pieceDepart_.get()->couleur_)))
		{
			// Si oui, on annule le d�placement
			modifierCase(coordonneesDestination, &pieceDestination_);
			modifierCase(coordonneesInitiales, &pieceDepart_);
			cout << "Ce mouvement mettrait le roi de la " << pieceDepart_.get()->nature_ << " en echec! " << endl;
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
		// Cette boucle Do While s'assure de la legalite du chemin en testant divers r�gles:
		prochaineCase = chemin[etapeChemin];
		// Note: On cherche la prochaine case au d�but de la boucle pour pouvoir effectuer des tests sur la case finale si besoin est
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
	} while (prochaineCase != destination); // Tant que la destination finale n'a pas �t� atteinte, on continue de suivre le chemin
	return true; // Si aucun des tests n'a �chou�, le mouvement est jug� l�gal 
}

//Methode qui permet d'afficher les informations d'une case precise, on passe en parametre les coordonnees de la case
void Echiquier::afficherInfosCase(pair<int, int> coordonnees) {
	cout << "La case aux coordonnees: " << coordonnees.first << ',' << coordonnees.second << endl;
	cout << "Est une " << tableau_[coordonnees.first][coordonnees.second].get()->nature_;

	cout << " de couleur " << tableau_[coordonnees.first][coordonnees.second].get()->couleur_ << endl;
}//]

pair<int, int> Echiquier::trouverPiece(std::string nature, std::string couleur) {

	// Maybe use method pattern instead
	if (couleur == "Noir") {
		for (int i = 0; i < equipes_[0].nMembres_; i++)
		{
			pair<int, int> membre = equipes_[0].listeDesCasesMembres_[i];
			if (tableau_[membre.first][membre.second].get()->nature_ == nature)
			{
				return membre;
			}
		}
	}
	else if(couleur == "Blanc") {
		for (int i = 0; i < equipes_[0].nMembres_; i++)
		{
			pair<int, int> membre = equipes_[0].listeDesCasesMembres_[i];
			if (tableau_[membre.first][membre.second].get()->nature_ == nature)
			{
				return membre;
			}
		}
	}
	// Ajouter une exception pour le cas o� aucun if n'est satisfait
}