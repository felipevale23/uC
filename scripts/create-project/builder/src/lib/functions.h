// Copyright 2022 felip
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "config.h"

// Passando valores de texto para um array de char;

void init()
{

}

void registers()
{

    // Configuração do Registrador INTCON
    GIE = 1;  // Habilitação geral das interrupções
    PEIE = 1; // Habilitação dos periféricos
    INTE = 1; // Habilitação de interrupção externa

    // Configuração do Registrador OPTION_REG
    nRBPU = 1;
    INTEDG = 1; // interrupção externa por borda de subida
    T0CS = 0;
    T0SE = 0;
    PSA = 0;
    OPTION_REGbits.PS = 0b001; // configura timer0 prescaler 1:4
    // OPTION_REG = 0x81;        // configura timer0 prescaler 1:4

    // Configuração do TIMER 0
    TMR0 = 0x06;
    TMR0IE = 1;
    TMR0IF = 0;

    ANSEL = 0;  // Configura os pinos AN analógicos como digitais
    ANSELH = 0; // Configura os pinos AN analógicos como digitais
    C1ON = 0;   // Desabilita os comparadores
    C2ON = 0;   // Desabilita os comparadores

    // Configuração do Registrador PORTs
    TRISA = 0x3F;
    TRISB = 0x00; // Pino 0 da porta B como input

}
