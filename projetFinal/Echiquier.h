#pragma once
#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "Piece.h"
#include "Roi.h"
#include "Cavalier.h"
#include "Tour.h"
#include "Equipe.h"

class Echiquier {
private:
	std::shared_ptr<piece> tableau_[8][8]; // G�neration d'un �chiquier de 8x8 
	Equipe equipes_[2];
public:
	Echiquier(Equipe equipe1 = Equipe("Equipe noire", "Noir"), Equipe equipe2 = Equipe("Equipe blanche", "Blanc"));

	// Vu que cette fonction utilise un template, il est n�cessaire qu'elle soit impl�ment�e dans le hpp ou le main directement
	template <class TypePiece>
	void modifierCase(const std::pair<int, int> coordonnees, const std::shared_ptr<TypePiece>* remplacement) {
		// On vide la case par pr�caution pour �viter des oublis au niveau de la gestion d'�quipes
		viderCase(coordonnees);
		// L'usage du template TypePiece permet d'�viter l'object slicing 
		tableau_[coordonnees.first][coordonnees.second] = *remplacement;
		// On r�attribue une �quipe � la pi�ce en fonction de sa nouvelle couleur
		attribuerEquipe(coordonnees);
	};
	void viderCase(const std::pair<int, int> coordonnees);
	void deplacerPiece(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination);
	bool verifierLegaliteMouvement(const std::vector<std::pair<int, int>>, const std::pair<int, int> destination, std::string couleurPiece);
	void afficherEchiquier();
	void afficherInfosCase(std::pair<int,int> coordonnees);
	// Fonction pour d�terminer � quelle �quipe une case appartient 
	int determinerEquipe(std::pair<int, int> coordonnees);
	// Fonction pour modifier les �quipes:
	void attribuerEquipe(std::pair<int, int> coordonnes);
	// Fonction pour afficher les membres d'une �quipe
	void afficherMembresEquipe(std::string nom);
	// Verifier la condition d'�chec
	bool verifierEchec(std::pair<int,int> positionRoi);
	bool validerMouvement(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination);
	std::pair<int, int> trouverPiece(std::string nature, std::string couleur);
};






