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
class Echiquier {
private:
	std::shared_ptr<piece> tableau_[8][8]; // Géneration d'un échiquier de 8x8 
	Equipe equipes_[2];
public:
	Echiquier(Equipe equipe1 = Equipe("Equipe noire", "Noir"), Equipe equipe2 = Equipe("Equipe blanche", "Blanc"));
	template <class TypePiece>
	void modifierCase(const std::pair<int, int> coordonnees, const std::shared_ptr<TypePiece>* remplacement);
	void viderCase(const std::pair<int, int> coordonnees);
	void deplacerPiece(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination);
	bool verifierLegaliteMouvement(const std::vector<std::pair<int, int>>, const std::pair<int, int> destination, std::string couleurPiece);
	void afficherEchiquier();
	void afficherInfosCase(std::pair<int,int> coordonnees);
	// Fonction pour déterminer à quelle équipe une case appartient 
	int determinerEquipe(std::pair<int, int> coordonnees);
	// Fonction pour modifier les équipes:
	void attribuerEquipe(std::pair<int, int> coordonnes);
	// Fonction pour afficher les membres d'une équipe
	void afficherMembresEquipe(std::string nom);
	
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
