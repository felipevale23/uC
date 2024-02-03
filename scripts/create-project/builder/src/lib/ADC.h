#define SBIT_ADON 0 // Valor de 0 para SBIT_ADON
#define SBIT_CHS0 2 // Valor de 2 para SBIT_CHS0, já que com ele vamos //deslocar o valor do canal analógico dentro do ADCON0
#define SBIT_ADFM 7 // Valor de 7 para SBIT_ADFM para atribuir definição //de justificado a direita ou esquerda

void ADC_Init() // Inicializamos o ADC
{
  ADCON0 = 0x80;             // //Selecionar clock de conversão para 20 MHz , Fosc/32 e ADC desabilitado
  ADCON1 = (1 << SBIT_ADFM); // O resultado do ADC é justificado à direita.
}

unsigned int ADC_read(unsigned char canal)
{
  ADCON0 = (1 << SBIT_ADON) | (canal << SBIT_CHS0); // seleciona o canal requerido e
  habilita o ADC
      Delay_ms(2); // Tempo de aquisição(espera que o capacitor de HOLD seja carregado)
  GO_bit = 1;      // Começa a conversão do ADC
  while (GO_bit == 1)
    ; // Espera que a conversão esteja completa
  // GO_bit será zerado automaticamente quando a conversão estiver completa
  return ((ADRESH << 8) | ADRESL); // retorna o resultado justificado de 10 bits
}
// Função para mostrar duas/tres casas decimais
