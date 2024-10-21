/*
 * main_cpp.hpp
 *
 *  Created on: Oct 16, 2024
 *      Author: mdejeante
 */

#ifndef CPP_PERIPH_CPP_HPP_
#define CPP_PERIPH_CPP_HPP_


#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32l1xx_hal.h"
#include "max7219_Yncrea2.h"
#include "main.h"

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#include <iostream>
#include <string>

class Periph {
private:
    std::string type;

public:
    Periph(const std::string& type) : type(type) {
        //std::cout << "Le peripherique " << type << " est active." << std::endl;
    }

    virtual void ON(){
        //activation du périph
    }

    virtual void OFF(){
        //désactivation du périph
    }

    virtual ~Periph(){
        //std::cout << "Le peripherique " << type << " est detruit." << std::endl;
    }
};

class Moteur : public Periph{
public : 
    Moteur(const std::string& nom) : Periph(nom) {}

    void ON() override {
        HAL_TIM_PWM_Init(&htim3);
	    HAL_TIM_Base_Start(&htim3);
	    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	    htim3.Instance->CCR1 = 250;
    }

    void OFF() override {
        htim3.Instance->CCR1 = 0;
	    HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1);
    }

    void Sequence(){
        ON();
        HAL_Delay(delai);
        OFF();
        HAL_Delay(delai);
    }
};

class Buzzer : public Periph{
public :
    Buzzer(const std::string& nom) : Periph(nom) {}

    void ON() override {
        HAL_TIM_PWM_Init(&htim3);
	    HAL_TIM_Base_Start(&htim3);
	    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
    }

    void OFF() override {
	    HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_2);
    }

    void Sequence(){
        ON();
        HAL_Delay(delai);
        OFF();
        HAL_Delay(delai);
    }
};

class Seg : public Periph{
public :
    Seg(const std::string& nom) : Periph(nom) {}

    void ON() override {
        MAX7219_Clear();
        MAX7219_Init();
        for (int i=1; i<5;i++){
            MAX7219_DisplayChar(i,'0',0);
        }
    }

    void OFF() override {
        MAX7219_Clear();
    }

    void Sequence(){
        ON();
        HAL_Delay(delai);
        OFF();
        HAL_Delay(delai);
    }
};

class LEDs : public Periph{
public :
    LEDs(const std::string& nom) : Periph(nom) {}

    void ON() override {
        HAL_GPIO_WritePin(GPIOB, L0_Pin|L1_Pin|L2_Pin|L3_Pin|L4_Pin|L5_Pin|L6_Pin|L7_Pin, GPIO_PIN_SET);
    }

    void OFF() override {
        HAL_GPIO_WritePin(GPIOB, L0_Pin|L1_Pin|L2_Pin|L3_Pin|L4_Pin|L5_Pin|L6_Pin|L7_Pin, GPIO_PIN_RESET);
    }

    void Sequence(){
        ON();
        HAL_Delay(delai);
        OFF();
        HAL_Delay(delai);
    }
};

#endif

#endif /* CPP_PERIPH_CPP_HPP_ */
