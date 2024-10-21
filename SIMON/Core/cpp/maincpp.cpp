#include "mainhpp.hpp"
#include "main.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

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
