#define RS RB0
#define EN RB2
#define D4 RB4
#define D5 RB5
#define D6 RB6
#define D7 RB7

#define _LCD_CLEAR 0x01                // Clear display
#define _LCD_4_BIT_MODE 0x02           // 4bit mode
#define _LCD_DECREMENT_CURSOR 0x04     // Decrement cursor (shift cursor to left)
#define _LCD_INCREMENT_CURSOR 0x06     // Increment cursor (shift cursor to right)
#define _LCD_SHIFT_DISPLAY_LEFT 0x07   // Shift display left
#define _LCD_SHIFT_DISPLAY_RIGHT 0x05  // Shift display right
#define _LCD_SET_FIRST_LINE_8BIT 0x30  // Function Set: 8-bit, 1 Line, 5x7 Dots
#define _LCD_SET_SECOND_LINE_8BIT 0x38 // Function Set: 8-bit, 2 Line, 5x7 Dots
#define _LCD_SET_FIRST_LINE_4BIT 0x20  // Function Set: 4-bit, 1 Line, 5x7 Dots
#define _LCD_SET_SECOND_LINE_4BIT 0x28 // Function Set: 4-bit, 2 Line, 5x7 Dots
#define _LCD_TURN_OFF 0x08             // Display Off and Cursor Off
#define _LCD_TURN_ON 0x0E              // Display On and Cursor On
#define _LCD_DISPLAY_ON 0xC0           // Turn on cursor
#define _LCD_CURSOR_ON 0x0E            // Turn on cursor
#define _LCD_CURSOR_OFF 0x0C           // Turn off cursor
#define _LCD_BLINK_CURSOR_ON 0x0F      // Blink cursor on
#define _LCD_SHIFT_LEFT 0x18           // Shift display left without changing display data RAM
#define _LCD_SHIFT_RIGHT 0x1E          // Shift display right without changing display data RAM
#define _LCD_MOVE_CURSOR_LEFT 0x10     // Move cursor left without changing display data RAM
#define _LCD_MOVE_CURSOR_RIGHT 0x14    // Move cursor right without changing display data RAM
#define _LCD_CURSOR_HOME 0x80          // Move cursor to the 1st row
#define _LCD_SECOND_ROW 0xC0           // Move cursor to the 2nd row
#define _LCD_UNDERLINE_ON 0x0E         // Underline cursor on

void Lcd_Port(char a)
{
    if (a & 1)
        D4 = 1;
    else
        D4 = 0;

    if (a & 2)
        D5 = 1;
    else
        D5 = 0;

    if (a & 4)
        D6 = 1;
    else
        D6 = 0;

    if (a & 8)
        D7 = 1;
    else
        D7 = 0;
}
void Lcd_Cmd(char a)
{
    RS = 0; // => RS = 0
    Lcd_Port(a);
    EN = 1; // => E = 1
    __delay_ms(4);
    EN = 0; // => E = 0
}

Lcd_Clear()
{
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b)
{
    char temp, z, y;
    if (a == 1)
    {
        temp = 0x80 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    }
    else if (a == 2)
    {
        temp = 0xC0 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    }
}

void Lcd_Init()
{
    Lcd_Port(0x00);
    __delay_ms(20);
    Lcd_Cmd(0x03);
    __delay_ms(5);
    Lcd_Cmd(0x03);
    __delay_ms(11);
    Lcd_Cmd(0x03);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x08);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x06);
}

void Lcd_Write_Char(char a)
{
    char temp, y;
    temp = a & 0x0F;
    y = a & 0xF0;
    RS = 1;           // => RS = 1
    Lcd_Port(y >> 4); // Data transfer
    EN = 1;
    __delay_us(40);
    EN = 0;
    Lcd_Port(temp);
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void Lcd_Write_String(char *a)
{
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right()
{
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left()
{
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x08);
}