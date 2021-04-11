#pragma once
#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class deplacable{
	virtual void afficher() = 0;
	virtual std::vector<std::pair<int, int>> trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) = 0; // Retourne un chemin si possible
	virtual bool demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) = 0; // Demande un mouvement
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
	void modifierCase(const std::pair<int, int> coordonnees, const shared_ptr<TypePiece>* remplacement);
	void viderCase(const std::pair<int, int> coordonnees);
	void deplacerPiece(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination);
	bool verifierLegaliteMouvement(const std::vector<std::pair<int, int>>, const std::pair<int, int> destination);
	void afficherEchiquier();
	void afficherInfosCase(std::pair<int,int> coordonnees);
	
	
};

class Tour : public piece {
private:
public:
	Tour(string nature, string couleur);
	/*void afficher() override;*/
	std::vector<std::pair<int, int>> trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
	bool demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
};

bool Tour::demanderMouvement(const std::pair<int, int> depart, const pair<int, int> destination) {
	if (destination.first != depart.first && destination.second != depart.second) {
		return false;
	}
	else
		return true;
}

vector<pair<int, int>> Tour::trouverChemin(const std::pair<int, int> depart, pair<int, int> destination) {
	vector<pair<int, int>> chemin;
	if (depart.first != destination.first) {
		if (depart.first > destination.first) {
			for (int i = depart.first - 1; i >= destination.first; i--) {
				pair<int, int> etape(i, depart.second);
				chemin.push_back(etape);
			}
		}
		else
		{
			for (int i = depart.first + 1; i <= destination.first; i++)
			{
				pair<int, int> etape(i, depart.second);
				chemin.push_back(etape);
			}
		}
	}
	else
	{
		if (depart.second > destination.second) {
			for (int i = depart.second - 1; i >= destination.second; i--)
			{
				pair<int, int> etape(depart.first, i);
				chemin.push_back(etape);
			}
		}
		else
		{
			for (int i = depart.second + 1; i <= destination.second; i++)
			{
				pair<int, int> etape(depart.first, i);
				chemin.push_back(etape);
			}
		}
	}
	return chemin;
}

class Cavalier : public piece {
private:
public:
	Cavalier(string nature, string couleur);
	/*void afficher() override;*/
	std::vector<std::pair<int, int>> trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
	bool demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
};

bool Cavalier::demanderMouvement(const std::pair<int, int> depart, const pair<int, int> destination) {
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

std::vector<std::pair<int, int>> Cavalier::trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) {
	vector<pair<int, int>> chemin;
	chemin.push_back(destination);
	return chemin;
}

