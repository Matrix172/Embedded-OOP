/*
 * main_cpp.hpp
 *
 *  Created on: Oct 16, 2024
 *      Author: mdejeante
 */

#ifndef CPP_MAIN_CPP_HPP_
#define CPP_MAIN_CPP_HPP_

extern int statut;
extern int nb_max;
extern int delai;

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32l1xx_hal.h"
#include "max7219_Yncrea2.h"
extern int uaction;
void main_cpp();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#include "periphhpp.hpp"

#include <iostream>
#include <string>
#include <vector>  // Inclusion de la bibliothèque <vector>
#include <cstdlib> // Pour rand() et srand(

extern void showaction(int action);
extern void MAX7219_Clear(void);
extern void MAX7219_Init(void);
extern void MAX7219_DisplayChar(char digit, char character, char dp);

class A
{
public:
	// Constructeur par défaut
	A()
	{
		std::cout << "Constructeur de A appelé" << std::endl;
	}

	// Méthode hello()
	void hello(void)
	{
		std::cout << "Hello CPP" << std::endl;
	}

	// Destructeur
	~A()
	{
		std::cout << "Destructeur de A appelé" << std::endl;
	}
};

class Joueur
{
private:
	std::string nom;
	int score;

public:
	Joueur(const std::string &nomJoueur) : nom(nomJoueur), score(0) {}

	void augmenterScore() { score++; }

	int getScore() const { return score; }
	std::string getNom() const { return nom; }
};

class SimonGame
{
private:
	std::vector<int> sequence;													  // Séquence d'actions
	std::vector<int> sequenceUser;												  // Séquence d'actions
	std::vector<std::string> listeactions = {"Moteur", "Buzzer", "LEDs", "7Seg"}; // Les noms des actions

public:
	// Constructeur qui initialise la graine pour le générateur de nombres aléatoires
	SimonGame()
	{
		int seed = HAL_GetTick(); // Utiliser HAL_GetTick() pour obtenir une source pseudo-aléatoire
		srand(seed);			  // Initialiser la graine avec ce compteur
	}

	// Méthode pour créer une nouvelle séquence d'actions
	void creationSequence()
	{
		for (int i = 0; i < nb_max; i++)
		{
			int action = rand() % 4; // Générer une action aléatoire (entre 0 et 3)
			printf("action %d\r\n", action);
			sequence.push_back(action); // Ajouter l'action à la séquence
		}
	}

	// Méthode pour montrer la séquence actuelle
	void montrerSequence()
	{
		std::cout << "Simon montre la séquence : ";
		for (int action : sequence) // Parcourir chaque action dans la séquence
		{
			std::cout << listeactions[action] << " "; // Afficher le nom de l'action
			showaction(action);
		}
		std::cout << std::endl; // Fin de ligne après avoir affiché toute la séquence
	}

	void vidersequence()
	{
		sequenceUser.clear();
		uaction = 5;
	}

	void vidersequences(){
		sequence.clear();
		sequenceUser.clear();
		uaction = 5;
	}

	// Demande au joueur de répéter la séquence
	void saisirSequence()
	{
		while (sequenceUser.size() != 4)
		{
			switch (uaction)
			{
			case 0:
				std::cout << "Moteur" << std::endl;
				sequenceUser.push_back(uaction);
				uaction = 5;
				break;
			case 1:
				std::cout << "Buzzer" << std::endl;
				sequenceUser.push_back(uaction);
				uaction = 5;
				break;
			case 2:
				std::cout << "LEDs" << std::endl;
				sequenceUser.push_back(uaction);
				uaction = 5;
				break;
			case 3:
				std::cout << "7Seg" << std::endl;
				sequenceUser.push_back(uaction);
				uaction = 5;
				break;
			default:
				break;
			}
			HAL_Delay(500); // Délai pour récupérer un vrai appui
		}
	}

	bool sequencecompare()
	{
		if (sequence.size() != sequenceUser.size())
		{
			std::cout << "Les sequences ont des tailles differentes." << std::endl;
			return false;
		}

		/*
		for (int i : sequence) {
			std::cout << sequence[i] << std::endl;
		}
		for( int i:sequenceUser){
			std::cout << sequenceUser[i] << std::endl;
		}
		*/


		// Comparaison des éléments un par un
		for (size_t i = 0; i < sequence.size(); i++)
		{
			if (sequence[i] != sequenceUser[i])
			{
				std::cout << "Erreur a l element " << i << " : attendu "
						<< listeactions[sequence[i]] << " recu "
						<< listeactions[sequenceUser[i]] << std::endl;
				return false;
			}
		}

		std::cout << "Les sequences correspondent !" << std::endl;
		vidersequences();
		return true;
	}
};

#endif

#endif /* CPP_MAIN_CPP_HPP_ */
