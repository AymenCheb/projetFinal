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
using namespace std;

/**
* Programme qui implément un jeu d'échecs
* \file   main.cpp
* \author Chebbi Mohamed Aymen, Jaafar Hady, Panoyan Arthur
* \date   12 avril 2021
* Créé le 08 avril 2021
*/



void testPartie1() {
	string sepratation = " \n --------------------------------------------------------------- \n";
	cout << "Tableau initial" << endl;
	cout << '\n';
	Echiquier echiquier;
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	pair<int, int> nouvelleCoordonnees, coordonneesInitiales;
	// Test: déplacer une case vide 
	nouvelleCoordonnees.first = 7;
	nouvelleCoordonnees.second = 7;
	cout << sepratation;
	cout << '\n';
	cout << "On demande le deplacement de la piece a la case (6,6), vers la case (7,7) :" << endl;
	cout << '\n';
	echiquier.deplacerPiece(coordonneesInitiales, nouvelleCoordonnees);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Coordonnees pour tester des deplacmeents de pieces
	nouvelleCoordonnees.first = 3;
	coordonneesInitiales.first = 5;
	nouvelleCoordonnees.second = 4;
	coordonneesInitiales.second = 4;

	// Creation d'une tour et test de deplacements
	//Creation de la tour et positionnement de la tour aux coordonnees
	Tour nouvellePiece("T", "Noir");
	shared_ptr<Tour> pointeurTour = make_shared<Tour>(nouvellePiece);
	cout << "On demande la modification de la case (5,4) en une tour: " << endl;
	cout << '\n';
	echiquier.modifierCase(coordonneesInitiales, &pointeurTour);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement legal de la tour
	cout << "On deplace la tour de 2 cases vers le haut" << endl;
	echiquier.deplacerPiece(coordonneesInitiales, nouvelleCoordonnees);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement illegal de la tour
	cout << "On tente de deplacer la tour en diagonale" << endl;
	pair<int, int> coordonneesTest(2, 3);
	echiquier.deplacerPiece(nouvelleCoordonnees, coordonneesTest);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';


	//Creation d'un cavalier et test de deplacements
	//Creation du cavalier et positionnement
	Cavalier premierCavalier("C", "Noir");
	shared_ptr<Cavalier> pointeurCavalier = make_shared<Cavalier>(premierCavalier);
	pair<int, int> coordonneesCavalier(5, 4);
	echiquier.modifierCase(coordonneesCavalier, &pointeurCavalier);
	cout << "On positionne un cavalier aux coordonnees (5,4)" << endl;
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement legal du cavalier
	pair<int, int> deplacementCavalier(3, 3);
	echiquier.deplacerPiece(coordonneesCavalier, deplacementCavalier);
	cout << "On deplace le cavaleir aux coordonnees (3,3)" << endl;
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacment illegal du cavalier
	pair<int, int> deplacementIllegalCavalier(2, 2);
	cout << "On essaie de deplacer le cavalier a la position (2,2)" << endl;
	echiquier.deplacerPiece(deplacementCavalier, deplacementIllegalCavalier);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';



	//Creation d'un roi et test de deplacements
	//Creation du roi et positionnement
	Roi premierRoi("R", "Noir");
	shared_ptr<Roi> pointeurRoi = make_shared<Roi>(premierRoi);
	pair<int, int> coordonneesRoi(2, 4);
	echiquier.modifierCase(coordonneesRoi, &pointeurRoi);
	cout << "On positionne le Roi aux coordonnees(2,4)" << endl;
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement legal du Roi
	pair<int, int> deplacementRoi(2, 5);
	echiquier.deplacerPiece(coordonneesRoi, deplacementRoi);
	cout << "On deplace le Roi aux coordonnees (2,5)" << endl;
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement illegal du roi
	pair<int, int> deplacementIllegalRoi(4, 6);
	cout << "On essaie de deplacer le Roi aux coordonnees (3,6), donc de deux cases." << endl;
	cout << '\n';
	echiquier.deplacerPiece(deplacementRoi, deplacementIllegalRoi);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';


	//Test pour deplacer une piece sur une case contenant une autre piece d'une meme couleur
	pair<int, int> deplacementRoiMange(3, 4);
	cout << "On essaie de deplacer le Roi aux coordonnees(3, 4), ou une piece alliee se trouve" << endl;
	cout << '\n';
	echiquier.deplacerPiece(deplacementRoi, deplacementRoiMange);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';


	//Test deplacer une tour alors q'une piece se trouve sur son chemin
	cout << "On essaie de deplacer la Tour des coordonnees (3,4) aux coordonnees (3,2), alors qu'un cavalier allie se trouve aux coordonnees (3,3)" << endl;
	nouvelleCoordonnees.first = 3;
	nouvelleCoordonnees.second = 4;
	pair<int, int> coordonneesDeplacementTour(3, 2);
	echiquier.deplacerPiece(nouvelleCoordonnees, coordonneesDeplacementTour);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';

	// Test: Affichage d'une case pour vérifier qu'elle a les bonnes coordonnees, nature/couleur... 
	nouvelleCoordonnees.first = 3;
	nouvelleCoordonnees.second = 4;
	cout << "On demande l'affichage de la case aux coordonnees:\n" << nouvelleCoordonnees.first << ',' << nouvelleCoordonnees.second << endl;
	echiquier.afficherInfosCase(nouvelleCoordonnees);
	cout << "On demande l'affichage des membres des deux équipes: " << endl;
	cout << '\n';
	echiquier.afficherMembresEquipe("Equipe noire");
	echiquier.afficherMembresEquipe("Equipe blanche");
	cout << sepratation;
	cout << '\n';
}

void testPartie2() {
	Echiquier echiquier;
	Roi roiNoir("R", "Noir");
	Roi roiBlanc("R", "Blanc");
	Tour tourBlanche("T", "Blanc");
	Tour tourNoir("T", "Noir");
	shared_ptr<Roi> pointeurRoiNoir = make_shared<Roi>(roiNoir);
	shared_ptr<Roi> pointeurRoiBlanc = make_shared<Roi>(roiBlanc);
	shared_ptr<Tour> pointeurTourBlanche = make_shared<Tour>(tourBlanche);
	shared_ptr<Tour> pointeurTourNoir = make_shared<Tour>(tourNoir);

	pair<int, int> crdRoiNoir(0, 0), crdTourNoir(0, 1), crdTourBlance(0, 2);
	// Test de la vérification de la mise en échecs: 
	echiquier.modifierCase(crdRoiNoir, &pointeurRoiNoir);
	echiquier.modifierCase(crdTourBlance, &pointeurTourBlanche);
	echiquier.modifierCase(crdTourNoir, &pointeurTourNoir);

	echiquier.afficherEchiquier();
	cout << '\n';
	pair<int, int> crdTN(1, 1);
	echiquier.afficherInfosCase(crdTN);
	echiquier.deplacerPiece(crdTourNoir, crdTN);
	echiquier.afficherEchiquier();

}


















//Constructeurs des differentes pieces
//[




// Implémentations relatives aux équipes
//[


//]




//Differentes methodes de la classe Echiquier
//[
//Cette methode permet de modifier une case precise de l'echiquier, en passant en parametre les coordonnees de la case, ainsi que la piece que l'on souhaite placer a cette case


//[
/*Implementation des methodes demanderMouvement specifiques a chaque piece : cette methode retourne, en fonction de la piece, true si cette piece
peut se deplacer de la maniere dont on souhaite le faire, ou false si le deplacement demander brise les regles de deplacement de cette piece*/






//]

//[
/*Implementation des methodes trouverChemin specifiques a chaque piece, cette methode retourne un vector contenant
les coordonnees des differentes cases par lesquelles une piece doit passer pour se rendre de sa case initiale jusqu'a celle
a laquelle on souahite la deplacer*/





//]


