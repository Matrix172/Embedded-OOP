/*
 * maincpp.cpp
 *
 *  Created on: Oct 16, 2024
 *      Author: mdejeante
 */
#include <mainhpp.hpp>
#include "stm32l1xx_hal.h"
#include <cstdlib>
#include <ctime>
#include <vector>

class Buzzer {
public:
    void beep() {
        // Code pour faire sonner le buzzer
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // Exemple de pin
        HAL_Delay(100);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }
};

class LEDs {
public:
    void lightUp(int index) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 << index, GPIO_PIN_SET); // Allumer la LED
    }

    void turnOff() {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_RESET); // Éteindre toutes les LEDs
    }
};

class Afficheur {
public:
    void showScore(int score) {
        // Code pour afficher le score sur l'afficheur 7 segments
    }

    void showElement(int element) {
        // Code pour afficher l'élément correspondant sur l'afficheur
    }
};

class Moteur {
public:
    void activate() {
        // Code pour activer le moteur
    }

    void deactivate() {
        // Code pour désactiver le moteur
    }
};

class Joueur {
private:
    int score;
    int niveau;
    std::vector<int> inputSequence; // Pour stocker les entrées du joueur

public:
    Joueur() : score(0), niveau(0) {}

    void increaseScore() {
        score++;
    }

    void nextLevel() {
        niveau++;
    }

    int getScore() const {
        return score;
    }

    int getNiveau() const {
        return niveau;
    }

    void reset() {
        score = 0;
        niveau = 0;
        inputSequence.clear();
    }

    void addInput(int input) {
        inputSequence.push_back(input);
    }

    const std::vector<int>& getInputSequence() const {
        return inputSequence;
    }

    void clearInput() {
        inputSequence.clear();
    }
};

class Jeu {
private:
    std::vector<int> sequence;
    Joueur joueur;
    Buzzer buzzer;
    LEDs leds;
    Afficheur afficheur;
    Moteur moteur;
    int speed;

public:
    Jeu() : speed(1000) {
        std::srand(static_cast<unsigned int>(std::time(0)));
    }

    void generateSequence() {
        sequence.push_back(std::rand() % 4); // 0-3 pour 4 éléments
    }

    void displaySequence() {
        for (int i = 0; i <= joueur.getNiveau(); i++) {
            int element = sequence[i];
            leds.lightUp(element);
            afficheur.showElement(element);
            buzzer.beep();
            HAL_Delay(speed);
            leds.turnOff();
            HAL_Delay(200); // Pause entre les éléments
        }
    }

    bool compareSequences() {
        const auto& playerSequence = joueur.getInputSequence();
        if (playerSequence.size() != sequence.size()) {
            return false; // La longueur des séquences est différente
        }

        for (size_t i = 0; i < playerSequence.size(); i++) {
            if (playerSequence[i] != sequence[i]) {
                return false; // Les éléments ne correspondent pas
            }
        }
        return true; // Les séquences correspondent
    }

    bool waitForInput() {
        for (int i = 0; i <= joueur.getNiveau(); i++) {
            int input = readButtonInput(); // Fonction à implémenter

            if (input == -1) { // Si aucun bouton n'est pressé
                i--; // Réessayer la même entrée
                continue;
            }

            joueur.addInput(input); // Ajouter l'entrée à la séquence du joueur

            // Vérifier si l'entrée est correcte jusqu'à présent
            if (!compareSequences()) {
                return false; // Mauvaise entrée
            }
        }
        return true; // Bonne entrée
    }

    void updateGame() {
        joueur.increaseScore();
        afficheur.showScore(joueur.getScore());
        joueur.nextLevel();
        speed = speed * 0.9; // Augmenter la vitesse
    }

    void resetGame() {
        joueur.reset();
        sequence.clear();
        speed = 1000;
    }

    void play() {
        while (1) {
            generateSequence();
            displaySequence();

            if (waitForInput()) {
                updateGame();
            } else {
                resetGame();
            }
        }
    }

    int readButtonInput() {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET) return 0; // Bouton 1
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET) return 1; // Bouton 2
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET) return 2; // Bouton 3
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_RESET) return 3; // Bouton 4
        return -1; // Aucun bouton pressé
    }
};

int main(void) {
    HAL_Init(); // Initialiser la HAL

    // Configurer les GPIO (LEDs, boutons, buzzer, moteur)
    configureGPIO();

    Jeu jeu; // Créer une instance du jeu
    jeu.play(); // Lancer le jeu
}

void configureGPIO() {
    // Activer l'horloge pour les ports GPIO
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configurer les LEDs
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3; // Ajuster selon tes pins
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Configurer les boutons
    GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7; // Ajuster selon tes pins
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Configurer le buzzer (si nécessaire)
    GPIO_InitStruct.Pin = GPIO_PIN_8; // Ajuster selon ton pin
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void main_cpp(void){
	// User C++ code

	while(1) {
		__NOP();
	}
}



