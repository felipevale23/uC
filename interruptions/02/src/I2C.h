void I2C1_Init(const unsigned long c)
{
  //SSPCON = 0b00101000;            //SSP Module as Master
  SSPCON = 0b10111000;  
  //SSPCON = 0x38; 
  SSPCON2 = 0;
  SSPADD = (20000000/(4*c))-1; //Setting Clock Speed
  SSPSTAT = 0;
  //TRISC3 = 1;                   //Setting as input as given in datasheet
  //TRISC4 = 1;                   //Setting as input as given in datasheet
  TRISC = 0xFF;
}

void I2C1_Wait()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //Transmit is in progress
}

void I2C1_Start()
{
  I2C1_Wait();    
  SEN = 1;             //Initiate start condition
}

void I2C1_RepeatedStart()
{
  I2C1_Wait();
  RSEN = 1;           //Initiate repeated start condition
}

void I2C1_Stop()
{
  I2C1_Wait();
  PEN = 1;           //Initiate stop condition
}

void I2C1_Write(unsigned d)
{
  I2C1_Wait();
  SSPBUF = d;         //Write data to SSPBUF
}

unsigned short I2C1_Read(unsigned short a)
{
  unsigned short temp;
  I2C1_Wait();
  RCEN = 1;
  I2C1_Wait();
  temp = SSPBUF;      //Read data from SSPBUF
  I2C1_Wait();
  ACKDT = (a)?0:1;    //Acknowledge bit
  ACKEN = 1;          //Acknowledge sequence
  return temp;
}

void I2C2_Init(short address) 
{
  SSPSTAT = 0x80;    
  SSPADD = address; //Setting address
  SSPCON = 0x36;    //As a slave device
  SSPCON2 = 0x01;
  TRISC3 = 1;       //Setting as input as given in datasheet
  TRISC4 = 1;       //Setting as input as given in datasheet
  GIE = 1;          //Global interrupt enable
  PEIE = 1;         //Peripheral interrupt enable
  SSPIF = 0;        //Clear interrupt flag
  SSPIE = 1;        //Synchronous serial port interrupt enable
}