#pragma once
#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include <memory>


class deplacable{
	virtual void afficher() = 0;
	virtual std::vector<std::pair<int, int>> trouverChemin(const std::pair<int, int> destination) = 0; // Retourne un chemin si possible
	virtual bool demanderMouvement(const std::pair<int, int> destination) = 0; // Demande un mouvement
};
class piece: private deplacable {
protected:
	std::string nature_ = "X";
	std::string couleur_ = "vide";
	std::pair<int, int> coordonnees_;
public:
	piece(std::pair<int, int> maCase);
	piece(std::string nature, std::string couleur, std::pair<int, int> maCase); // Rajouter la couleur au concstructeur 
	void afficher() override;
	void afficherCoordonnees();
	std::vector<std::pair<int, int>> trouverChemin(const std::pair<int, int> destination) override;
	bool demanderMouvement(const std::pair<int, int> destination) override;
	friend class Echiquier;
};


class Echiquier {
private:
	std::unique_ptr<piece> tableau_[8][8]; // Géneration d'un échiquier de 8x8 
public:
	Echiquier();
	template <class TypePiece>
	void modifierCase(const std::pair<int, int> coordonnees, const TypePiece& remplacement);
	void viderCase(const std::pair<int, int> coordonnees);
	void deplacerPiece(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination);
	bool verifierLegaliteMouvement(const std::vector<std::pair<int, int>>, const std::pair<int, int> destination);
	void afficherEchiquier();
	void afficherInfosCase(std::pair<int,int> coordonnees);
	
	
}; 