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

#define _XTAL_FREQ 20000000

// CONFIG1
#pragma config FOSC = XT   // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF  // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON  // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON  // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF    // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF   // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF  // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF   // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
#pragma config DEBUG = OFF
// CONFIG2
#pragma config BOR4V = BOR40V // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF      // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>

#include <htc.h>