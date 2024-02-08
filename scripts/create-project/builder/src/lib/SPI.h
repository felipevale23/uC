#include <xc.h>

void SPI_Initialize_Master () 
{
    TRISC5 = 0; //
    SSPSTAT = 0b00000000 ; // page 74/234
    SSPCON = 0b00100000 ; //pg 75/234
    TRISC3 = 0; // Set as output to slave mode
}

void SPI_Write ( char incoming ) 
{
    SSPBUF = incoming; // Write user-supplied data to buffer
}

unsigned SPI_Ready2Read () 
{
    if (SSPSTAT & 0b00000001) 
        return 1;
    else
        return 0;
}

char SPI_Read() // Leia os dados recebidos
{
    while (!SSPSTATbits.BF); // Segure até que o bit BF seja definido, para garantir que todos os dados sejam lidos
    return(SSPBUF); // retorna os dados lidos
}
