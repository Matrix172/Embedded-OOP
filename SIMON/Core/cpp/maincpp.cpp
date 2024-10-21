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
/*
void Motor_Pulse(){
	HAL_TIM_PWM_Init(&htim3);
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	htim3.Instance->CCR1 = 250;
	HAL_Delay(delai);
	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1);
}

void Buzzer_Pulse(){
	int indice = 5;
	for (int i =0; i<indice; i++){
		HAL_TIM_Base_Start(&htim3);
		HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
		HAL_Delay(delai/5);
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_2);
	}
}

void LEDs_Pulse(){
	HAL_GPIO_WritePin(GPIOB, L0_Pin|L1_Pin|L2_Pin|L3_Pin|L4_Pin|L5_Pin|L6_Pin|L7_Pin, GPIO_PIN_SET);
	HAL_Delay(delai/2);
	HAL_GPIO_WritePin(GPIOB, L0_Pin|L1_Pin|L2_Pin|L3_Pin|L4_Pin|L5_Pin|L6_Pin|L7_Pin, GPIO_PIN_RESET);
	HAL_Delay(delai/2);
}

void Seg_Pulse(){
	MAX7219_Clear();
	MAX7219_Init();
	MAX7219_DisplayChar(1,'0', 0); // Pas de point décimal
	MAX7219_DisplayChar(2,'0', 0); // Avec point décimal
	MAX7219_DisplayChar(3,'0', 0); // Pas de point décimal
	MAX7219_DisplayChar(4,'0', 0);
	HAL_Delay(delai/6);
	MAX7219_Clear();
	MAX7219_Init();
}
*/

void showaction(int action) {
	Moteur moteur ("Moteur 1");
	Buzzer buzzer ("Buzzer 1");
	Seg seg ("SEG 1");
	LEDs leds ("Leds 1");

	switch (action) {
	case 0:
		printf("\r\nMoteur action\r\n");
		moteur.Sequence();
		//Motor_Pulse();
		break;
	case 1:
		printf("\r\nBuzzer action\r\n");
		buzzer.Sequence();
		// Buzzer_Pulse();
		break;
	case 2:
		printf("\r\nLEDs action\r\n");
		leds.Sequence();
		// LEDs_Pulse();
		break;
	case 3:
		printf("\r\n7Seg action\r\n");
		seg.Sequence();
		// Seg_Pulse();
		break;
	default:
		printf("\r\nAction inconnue\r\n");
		break;
	}
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
		simon.creationSequence();
		simon.montrerSequence();
		simon.saisirSequence();
		simon.sequencecompare();

		/*
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
		*/
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
