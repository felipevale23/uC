#include "config.h"
#include "functions.h"

// Protótipos das funções;
void init();
void handleClick();
void setLEDs();
void setDisplay();
void showDisplay();
void clear();

// Código Principal;
void main (){

    //Iniciando as configurações
    init();

    while(1){

        handleClick(); //Analisando o estado das entradas
        setLEDs();     //Configurando os leds conforme a entrada
        showDisplay(); //Mostrando o resultado no Display LCD.

    }
}

