#pragma once
#include <utility>
#include <string>
#include <iostream>
#include <memory>


class deplacable{
	virtual void afficher() = 0;
	virtual std::pair<int, int>* trouverChemin(const std::pair<int, int> destination) = 0; // Retourne un chemin si possible
	virtual bool demanderMouvement(const std::pair<int, int> destination) = 0; // Demande un mouvement
};
class piece: private deplacable {
private:
	std::string nature_;
	std::string couleur_;
public:
	piece();
	piece(std::string nature);
	void afficher() override;
	std::pair<int, int>* trouverChemin(const std::pair<int, int> destination) override;
	bool demanderMouvement(const std::pair<int, int> destination) override;
	friend class Echiquier;
};


class Echiquier {
private:
	std::unique_ptr<piece> tableau_[8][8]; // Géneration d'un échiquier de 8x8 
public:
	Echiquier();
	void modifierCase(const std::pair<int, int> coordonnees, const piece remplacement);
	void viderCase(const std::pair<int, int> coordonnees);
	void deplacerPiece(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination);
	bool verifierLegaliteMouvement(const std::pair<int, int> chemin[], const std::pair<int, int> destination);
	void afficherEchiquier();
	
	
};