/*
 * main_cpp.hpp
 *
 *  Created on: Oct 16, 2024
 *      Author: mdejeante
 */

#ifndef CPP_MAIN_CPP_HPP_
#define CPP_MAIN_CPP_HPP_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l1xx_hal.h"
void main_cpp();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <iostream>
class A {
public:
    // Constructeur par défaut (optionnel si tu n'as pas besoin d'initialisation spécifique)
    A() {
        std::cout << "Constructeur de A appelé" << std::endl;
    }

    // Méthode hello()
    void hello(void) {
        std::cout << "Hello CPP" << std::endl;
    }

    // Destructeur
    ~A() {
        std::cout << "Destructeur de A appelé" << std::endl;
    }
};
#endif

#endif /* CPP_MAIN_CPP_HPP_ */
