#include "mainhpp.hpp"
#include "main.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void Display_go(){
	MAX7219_Clear();
	MAX7219_Init();
	MAX7219_DisplayChar(2,'G', 0); // Avec point décimal
	MAX7219_DisplayChar(3,'O', 0); // Pas de point décimal
}
void Display_joueur(){
	MAX7219_Clear();
	MAX7219_Init();
	if (statut==1){
		MAX7219_DisplayChar(2,'J', 0); // Avec point décimal
		MAX7219_DisplayChar(3,'1', 0); // Pas de point décimal
	}
	else if (statut==2){
		MAX7219_DisplayChar(2,'J', 0); // Avec point décimal
		MAX7219_DisplayChar(3,'2', 0); // Pas de point décimal
	}
	else{
		MAX7219_Clear();
	}
}

void Display_score(Joueur joueur){
	if ((joueur.getScore())<10){
		MAX7219_Clear();
		MAX7219_Init();
		MAX7219_DisplayChar(1,'S', 0); // Avec point décimal
		MAX7219_DisplayChar(2,'C', 1); // Pas de point décimal
		MAX7219_DisplayChar(3,'0', 0); // Avec point décimal
		MAX7219_DisplayChar(4,joueur.getScore(), 0); // Pas de point décimal
	}
	else if (joueur.getScore()>9){
		int nouveau_score=joueur.getScore()%10;
		MAX7219_Clear();
		MAX7219_Init();
		MAX7219_DisplayChar(1,'S', 0); // Avec point décimal
		MAX7219_DisplayChar(2,'C', 1); // Pas de point décimal
		MAX7219_DisplayChar(3,nouveau_score, 0); // Avec point décimal
		MAX7219_DisplayChar(4,'0', 0); // Pas de point décimal
	}
}

int get_nb_joueurs(){
	std::cout << "Veuillez entrer le nombre de joueurs (1 ou 2) : ";
	std::cin >> statut;  // Simule la récupération du nombre de joueurs via une entrée
	while (statut != 1 && statut != 2);
	return statut;
}

void partieSimon(int nb_joueurs)
{
	srand(time(0));  // Initialiser le générateur de nombres aléatoires

	// Création des joueurs
	Joueur J1("J1");
	Joueur J2("J2");
	Display_score(J1);


	// Instancier le jeu
	SimonGame simon;

	int tour = 0;
	bool partieEnCours = true;

	while (partieEnCours)
	{
		std::cout << "\n--- Tour " << ++tour << " ---" << std::endl;

		// Montrer la séquence
		simon.montrerSequence();

		// Joueur 1 doit entrer la séquence
		if (!simon.saisirSequence(J1))
		{
			partieEnCours = false;  // Fin de la partie si J1 fait une erreur
			break;
		}

		// Si 2 joueurs, Joueur 2 doit aussi entrer la séquence
		if (nb_joueurs == 2)
		{
			if (!simon.saisirSequence(J2))
			{
				partieEnCours = false;  // Fin de la partie si J2 fait une erreur
				break;
			}
		}

		// La séquence continue si tout le monde réussit
	}

	// Fin de partie, afficher les scores
	std::cout << "\nFin de la partie ! Scores : " << std::endl;
	std::cout << J1.getNom() << " : " << J1.getScore() << " points" << std::endl;
	if (nb_joueurs == 2)
	{
		std::cout << J2.getNom() << " : " << J2.getScore() << " points" << std::endl;
	}
}

void main_cpp(void) {

	// Attendre et récupérer le nombre de joueurs via une entrée
	int nombre_de_joueurs = get_nb_joueurs();

	// Démarrer la partie
	partieSimon(nombre_de_joueurs);
}
