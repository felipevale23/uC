#include "config.h"
#include "functions.h"

char txt1[], txt2[];

//Functions Prototypes
void init();
void showDisplay(char txt1, char txt2);
void handleClick();

//Main code
void main (){

    init();

    while(1){

        handleClick();
        showDisplay(txt1, txt2);

    }
}

