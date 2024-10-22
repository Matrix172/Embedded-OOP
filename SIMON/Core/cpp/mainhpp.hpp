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
extern int jeu;

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

	void DisplayScore()
	{
		if ((this->getScore()) < 10)
		{
			MAX7219_Clear();
			MAX7219_Init();
			MAX7219_DisplayChar(1, 'S', 0);					   // Avec point décimal
			MAX7219_DisplayChar(2, 'C', 1);					   // Pas de point décimal
			MAX7219_DisplayChar(4, this->getScore() + '0', 0); // Pas de point décimal
		}
		else if (this->getScore() > 9)
		{
			// Cas où le score est supérieur ou égal à 10
			int dizaines = this->getScore() / 10; // Extraire le chiffre des dizaines
			int unites = this->getScore() % 10;	  // Extraire le chiffre des unités

			MAX7219_Clear();
			MAX7219_Init();
			MAX7219_DisplayChar(1, 'S', 0);			   // Avec point décimal
			MAX7219_DisplayChar(2, 'C', 1);			   // Pas de point décimal
			MAX7219_DisplayChar(3, dizaines + '0', 0); // Affiche le chiffre des dizaines
			MAX7219_DisplayChar(4, unites + '0', 0);   // Affiche le chiffre des unités
		}
	}

	void DisplayJoueur()
	{
		std::string nomJoueur = this->getNom();

		MAX7219_Clear();
		MAX7219_Init();
		MAX7219_DisplayChar(2, 'J', 0); // Avec point décimal

		// Vérifiez si le nom n'est pas vide avant d'accéder au premier caractère
		if (!nomJoueur.empty())
		{
			char chiffre = nomJoueur[0];		// Obtenez le premier caractère
			MAX7219_DisplayChar(3, chiffre, 0); // Affiche le premier caractère du nom
		}
		else
		{
			// Gérer le cas où le nom est vide (si nécessaire)
			MAX7219_DisplayChar(3, ' ', 0); // Affiche un espace ou un autre caractère par défaut
		}
	}

	void affichage()
	{
		this->DisplayJoueur();
		HAL_Delay(2000);
		this->DisplayScore();
		HAL_Delay(2000);
	}
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
			// printf("action %d\r\n", action);
			sequence.push_back(action); // Ajouter l'action à la séquence
		}
	}

	// Méthode pour montrer la séquence actuelle
	void montrerSequence()
	{
		std::cout << "Simon montre la sequence : ";
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

	void vidersequences()
	{
		sequence.clear();
		sequenceUser.clear();
		uaction = 5;
	}

	// Demande au joueur de répéter la séquence
	void saisirSequence()
	{
		Moteur moteur("Moteur 1");
		Buzzer buzzer("Buzzer 1");
		Seg seg("SEG 1");
		LEDs leds("Leds 1");
		while (sequenceUser.size() != 4)
		{
			switch (uaction)
			{
			case 0:
				std::cout << "Moteur" << std::endl;
				moteur.SequenceU();
				sequenceUser.push_back(uaction);
				uaction = 5;
				break;
			case 1:
				std::cout << "Buzzer" << std::endl;
				buzzer.SequenceU();
				sequenceUser.push_back(uaction);
				uaction = 5;
				break;
			case 2:
				std::cout << "LEDs" << std::endl;
				leds.SequenceU();
				sequenceUser.push_back(uaction);
				uaction = 5;
				break;
			case 3:
				std::cout << "7Seg" << std::endl;
				seg.SequenceU();
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
