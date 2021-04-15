#pragma once
#include <string>
#include <iostream>
#include <vector>

class deplacable {
	virtual void afficher() = 0;
	virtual std::vector<std::pair<int, int>> trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) = 0; // Retourne un chemin si possible
	virtual bool demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) = 0; // Demande un mouvement, return true si la piece peut se deplacer de cette maniere , sinon false
};
class piece : private deplacable {
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