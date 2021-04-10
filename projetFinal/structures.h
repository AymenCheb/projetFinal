#pragma once
#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

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

class Tour : public piece {
private:
public:
	Tour(string nature, string couleur, pair<int,int> coordonneesInitiales);
	/*void afficher() override;*/
	std::vector<std::pair<int, int>> trouverChemin(const std::pair<int, int> destination) override;
	bool demanderMouvement(const std::pair<int, int> destination) override;
};

bool Tour::demanderMouvement(const pair<int, int> destination) {
	if (destination.first != coordonnees_.first && destination.second != coordonnees_.second) {
		return false;
	}
	else
		return true;
}

vector<pair<int, int>> Tour::trouverChemin(pair<int, int> destination) {
	vector<pair<int, int>> chemin;
	if (coordonnees_.first != destination.first) {
		if (coordonnees_.first > destination.first) {
			for (int i = coordonnees_.first - 1; i >= destination.first; i--) {
				pair<int, int> etape(i, coordonnees_.second);
				chemin.push_back(etape);
			}
		}
		else
		{
			for (int i = coordonnees_.first + 1; i <= destination.first; i++)
			{
				pair<int, int> etape(i, coordonnees_.second);
				chemin.push_back(etape);
			}
		}
	}
	else
	{
		if (coordonnees_.second > destination.second) {
			for (int i = coordonnees_.second - 1; i >= destination.second; i--)
			{
				pair<int, int> etape(coordonnees_.first, i);
				chemin.push_back(etape);
			}
		}
		else
		{
			for (int i = coordonnees_.second + 1; i <= destination.second; i++)
			{
				pair<int, int> etape(coordonnees_.first, i);
				chemin.push_back(etape);
			}
		}
	}
	return chemin;
}

