#pragma once
#include <utility>
#include <string>
#include <iostream>
#include <memory>


class deplacable{
	virtual void afficher() = 0;
	virtual std::pair<int, int>* trouverChemin(std::pair<int, int> destination) = 0; // Retourne un chemin si possible
	virtual void demanderMouvement(std::pair<int, int> destination) = 0; // Demande un mouvement
};
class piece {
private:
	std::string nature_;
	std::string couleur_;
public:
	piece();
	piece(std::string nature);
	void afficherNature();
};
class Echiquier {
private:
	std::unique_ptr<piece> tableau_[8][8]; // Géneration d'un échiquier de 8x8 
public:
	Echiquier();
	void modifierCase(const std::pair<int, int> coordonnees, const piece remplacement);
	void viderCase(const std::pair<int, int> coordonnees);
	bool verifierLegaliteMouvement(const std::pair<int, int> chemin[]);
	void executerMouvement(const std::pair<int, int> chemin[]);
	void afficherEchiquier();
	
	
};