#include "mainhpp.hpp"
#include "main.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void Display_gamestart(){
	MAX7219_Clear();
	MAX7219_Init();
	MAX7219_DisplayChar(1,'P', 0); // Avec point décimal
	MAX7219_DisplayChar(2,'R', 0); // Avec point décimal
	MAX7219_DisplayChar(3,'E', 0); // Pas de point décimal
	MAX7219_DisplayChar(4,'T', 0); // Pas de point décimal
	HAL_Delay(1000);
	MAX7219_Clear();
}

void Display_gameover(){
	MAX7219_Clear();
	MAX7219_Init();
	MAX7219_DisplayChar(2,'F', 0); // Avec point décimal
	MAX7219_DisplayChar(3,'I', 0); // Pas de point décimal
	MAX7219_DisplayChar(4,'N', 0); // Pas de point décimal
	HAL_Delay(2000);
	MAX7219_Clear();
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

void showaction(int action) {
	Moteur moteur ("Moteur 1");
	Buzzer buzzer ("Buzzer 1");
	Seg seg ("SEG 1");
	LEDs leds ("Leds 1");

	switch (action) {
	case 0:
		//printf("\r\nMoteur action\r\n");
		moteur.Sequence();
		break;
	case 1:
		//printf("\r\nBuzzer action\r\n");
		buzzer.Sequence();
		break;
	case 2:
		//printf("\r\nLEDs action\r\n");
		leds.Sequence();
		break;
	case 3:
		//printf("\r\n7Seg action\r\n");
		seg.Sequence();
		break;
	default:
		//printf("\r\nAction inconnue\r\n");
		break;
	}
}

void partieSimon(int nb_joueurs)
{
	srand(time(0));  // Initialiser le générateur de nombres aléatoires

	// Création des joueurs
	Joueur J1("1");
	Joueur J2("2");

	// Instancier le jeu
	SimonGame simon;

	int tour = 0;
	int nb_player = statut;
	bool partieEnCours = true;
	int joueurCourant = 1;  // Pour suivre quel joueur doit jouer

	while (partieEnCours)
	{
		std::cout << "\n--- Tour " << ++tour << " ---" << std::endl;

		// Alternance entre les joueurs
		if (joueurCourant == 1)
		{
			std::cout << "\nAu tour de " << J1.getNom() << " de jouer." << std::endl;
		}
		else if (joueurCourant == 2)
		{
			std::cout << "\nAu tour de " << J2.getNom() << " de jouer." << std::endl;
		}

		// Montrer la séquence par Simon
		simon.creationSequence();
		Display_gamestart();
		simon.montrerSequence();

		// Le joueur entre la séquence
		simon.vidersequence();
		simon.saisirSequence();

		// Comparer la séquence avec celle de Simon
		if (!simon.sequencecompare())
		{
			std::cout << "\n" << (joueurCourant == 1 ? J1.getNom() : J2.getNom()) << " a fait une erreur ! Fin de la partie." << std::endl;
			partieEnCours = false;
			if (nb_player==1){
				J1.affichage();
				Display_gameover();

			}
			else if (nb_player==2){
				J1.affichage();
				J2.affichage();
				Display_gameover();
			}
			else {
				MAX7219_Clear();
			}
			break;
		}
		else
		{
			if (joueurCourant == 1) {
				J1.augmenterScore();
				std::cout << "\nLe score de " << J1.getNom() << " est de : " << J1.getScore() << std::endl;
			} else {
				J2.augmenterScore();
				std::cout << "\nLe score de " << J2.getNom() << " est de : " << J2.getScore() << std::endl;
			}
		}

		// Alterner entre les joueurs
		if (nb_joueurs == 2)
		{
			joueurCourant = (joueurCourant == 1) ? 2 : 1;  // Alterner entre J1 et J2
		}
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
