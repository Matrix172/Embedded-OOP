/*
 * main_cpp.hpp
 *
 *  Created on: Oct 16, 2024
 *      Author: mdejeante
 */

#ifndef CPP_MAIN_CPP_HPP_
#define CPP_MAIN_CPP_HPP_

//extern int statut;
//extern void MAX7219_Init(void);
//extern void MAX7219_ShutdownStart(void);
//extern void MAX7219_ShutdownStop(void);
//extern void MAX7219_DisplayTestStart(void);
//extern void MAX7219_DisplayTestStop(void);
//extern void MAX7219_SetBrightness(char brightness);
//extern void MAX7219_Clear(void);
//extern void MAX7219_DisplayChar(char digit, char character, char dp);

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32l1xx_hal.h"
#include "max7219_Yncrea2.h"
void main_cpp();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <iostream>
#include <string>
#include <vector>  // Inclusion de la bibliothèque <vector>
extern int statut;

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
    //int score;

public:
    int score;
    Joueur(const std::string& nomJoueur) : nom(nomJoueur), score(0) {}

    void augmenterScore() { score++; }

    int getScore() const { return score; }
    std::string getNom() const { return nom; }
};

class SimonGame
{

public:
    // Montre la séquence actuelle
    void montrerSequence()
    {   
        std::cout << "Simon montre la séquence : ";
        //Générer une séquence et communiquer avec les périphériques
        std::cout << std::endl;
    }

    // Demande au joueur de répéter la séquence
    bool saisirSequence(Joueur& joueur)
    {   
        // Si le joueur réussi, on ajoute à son score.
        // Sinon, Game Over et le joueur qui a le + gagne.
    	return(false);
    }
};

#endif

#endif /* CPP_MAIN_CPP_HPP_ */
