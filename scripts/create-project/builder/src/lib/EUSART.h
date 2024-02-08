extern char dado;

/***************** Função para transmitir um caractere *************/
void TXCHR_USART(char dado1)
{
    while(TXIF_bit == 0); //espera pelo flag de interrupção de transmissão
    TXIF_bit = 0;
    TXREG = dado1; //espera que o flag de interrupção de transmissão fique em 1 o
    //qual indica que TXREG está pronto para outra transmissão
}

/******************** Função para transmitir uma string ************/
void TX_STRING_USART(const char *dado)
{
    unsigned int i = 0;
    while (dado[i] != '\0')
    TXCHR_USART(dado[i++]);
}//fim da função TX_STRING_USART()

/**************** Função INCIAR_USART ****************************/
void INICIAR_USART(const unsigned long Baud_Rate)
{
    SPBRG = (20000000UL/(long)(16*Baud_Rate))-1; // baud rate para Fosc = 20Mhz e BRGH=1
    SYNC_bit = 0; // habilita o modo assíncrono
    SPEN_bit = 1; //habilita pinos da porta serial
    CREN_bit = 1; //habilita a recepção
    TXIE_bit = 0; //desabilita a interrupção de transmissão
    RCIE_bit = 0; //desabilita a interrupção de recepção
    TX9_bit = 0; //transmissão de 8 bits de dados
    RX9_bit = 0; //recepção de 8 bits de dados
    TXEN_bit = 1; //habilita a transmissão
}