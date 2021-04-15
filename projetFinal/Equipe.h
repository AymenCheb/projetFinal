#pragma once
#include <string>
#include <iostream>
#include <vector>

class Equipe {
private:
	std::string nom_ = "Equipe vide";
	std::string couleur_ = "Aucune";
	std::vector<std::pair<int, int>> listeDesCasesMembres_;
	int nMembres_ = 0;
public:
	Equipe(const std::string nom = "Equipe vide", const std::string couleur = "Aucune");
	void ajouterMembre(const std::pair<int, int> nouvellesCoordonnees);
	void retirerMembre(const std::pair<int, int> coordonneesMembre);
	bool verifierPresenceMembre(std::pair<int, int> coordonnees);
	friend class Echiquier;
};