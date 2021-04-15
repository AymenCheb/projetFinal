#pragma once
#include "Piece.h"

class Tour : public piece {
private:
public:
	Tour(std::string nature, std::string couleur);
	std::vector<std::pair<int, int>> trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
	bool demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
};