 void registers()
{
    ANSEL = 0; // Configurar pinos AN como digital
    ANSELH = 0x23; // Configurar pinos ANS8,ANS9 e ANS13 como digital
    TRISB = 1; //Porta B entrada.
   
    //Selecionar clock de conversão para 20 MHz ,Fosc/32 ADCON0.ADCS1=1; ADCON0.ADCS0=0;
    C1ON_bit = C2ON_bit = 0; // Desabilita os comparadores
    TRISB = 0; //Porta B saída, conectada ao LCD
    BRGH_bit = 1; //EUSART funciona a alta velocidade e utiliza a equação mostrada para SPBRG.

    //Selecionar o formato do resultado, justificado à direita
    ADCON1.ADFM = 1;
    //Configurar tensão de referência, VDD e GND 
    ADCON1.VCFG1 = 0; 
    ADCON1.VCFG0 = 0;
    
    //Habilita o módulo ADC
    ADCON0.ADON = 1;

    //Selecionar canal de entrada do ADC, canal 0 RB2/AN8
    ADCON0.CHS0 = 0; 
    ADCON0.CHS1 = 0; 
    ADCON0.CHS2 = 0; 
    ADCON0.CHS3 = 1;
    
    //Selecionar clock de conversão para 20 MHz ,Fosc/32
    ADCON0.ADCS0=0;
    ADCON0.ADCS1=1;

    //Sem interrupções
    
   /************************ configuração da interrupção de recepção USART
   Esta configuração deve ir depois da função INICIAR_USART pq nesta estamos
   desabilitando a interrupção de recepção USART *******/

   RCIF_bit = 0; //desabilitamos o flag de interrupção de recepção USART
   RCIE_bit = 1; //Habilitamos a interrupção de recepção USART
   GIE_bit = 1; //Habilitamos a interrupção global
   PEIE_bit = 1; //Habilitamos a interrupção de perifericos
}// Fim das configurações de interrupção de recepção USART