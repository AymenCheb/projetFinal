#include <string>
#include <iostream>
#include <vector>
#include "Equipe.h"
using namespace std;

Equipe::Equipe(const std::string nom, const std::string couleur) {
	nom_ = nom;
	couleur_ = couleur;
};
void Equipe::ajouterMembre(pair<int, int> nouvellesCoordonnees) {

	if (!verifierPresenceMembre(nouvellesCoordonnees)); {
		listeDesCasesMembres_.push_back(nouvellesCoordonnees); // Ajoute le membre à la liste si il n'y est pas déjà
		nMembres_++;
	}
};
void Equipe::retirerMembre(const std::pair<int, int> coordonneesMembre) {
	for (int i = 0; i < nMembres_; i++)
	{
		if (listeDesCasesMembres_[i] == coordonneesMembre) {
			listeDesCasesMembres_.erase(listeDesCasesMembres_.begin() + i); // Supprime le membre de la liste
			nMembres_--;
		}
	}
};
bool Equipe::verifierPresenceMembre(std::pair<int, int> coordonnees) {
	for (int i = 0; i < nMembres_; i++)
	{
		if (listeDesCasesMembres_[i] == coordonnees)
			return true;
	}
	return false;
}