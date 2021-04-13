#pragma once
#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include <memory>

class deplacable{
	virtual void afficher() = 0;
	virtual std::vector<std::pair<int, int>> trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) = 0; // Retourne un chemin si possible
	virtual bool demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) = 0; // Demande un mouvement, return true si la piece peut se deplacer de cette maniere , sinon false
};
class piece: private deplacable {
protected:
	std::string nature_ = "X";
	std::string couleur_ = "vide";
public:
	piece();
	piece(std::string nature, std::string couleur); // Rajouter la couleur au concstructeur 
	void afficher() override;
	std::vector<std::pair<int, int>> trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
	bool demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
	friend class Echiquier;
};


class Echiquier {
private:
	std::shared_ptr<piece> tableau_[8][8]; // Géneration d'un échiquier de 8x8 
public:
	Echiquier();
	template <class TypePiece>
	void modifierCase(const std::pair<int, int> coordonnees, const std::shared_ptr<TypePiece>* remplacement);
	void viderCase(const std::pair<int, int> coordonnees);
	void deplacerPiece(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination);
	bool verifierLegaliteMouvement(const std::vector<std::pair<int, int>>, const std::pair<int, int> destination, std::string couleurPiece);
	void afficherEchiquier();
	void afficherInfosCase(std::pair<int,int> coordonnees);
	
	
};

class Tour : public piece {
private:
public:
	Tour(std::string nature, std::string couleur);
	std::vector<std::pair<int, int>> trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
	bool demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
};


class Cavalier : public piece {
private:
public:
	Cavalier(std::string nature, std::string couleur);
	std::vector<std::pair<int, int>> trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
	bool demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
};


//implementation de la piece Roi
class Roi :public piece {
private:
public:
	Roi(std::string nature, std::string couleur);
	std::vector<std::pair<int, int>>trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
	bool demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
};
