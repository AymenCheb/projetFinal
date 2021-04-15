#include <utility>
#include <string>
#include <iostream>
#include <memory>

#include "Piece.h"
#include "Roi.h"
#include "Cavalier.h"
#include "Tour.h"
#include "Equipe.h"
#include "Echiquier.h"
#include "Tests.h"
using namespace std;

int main() {
	cout << "On commence les tests: " << '\n' << "Tests livrable 1: " << endl;
	testPartie1();
	return 1;
}