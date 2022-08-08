//------------------------------------------------
// MAX7219_7Seg_Disp.cpp - Source File
// Library for Displaying Numbers & Chracters on
// MAX7219 8-Digit 7-Segment Display
// by: Anas Kuzechie (June, 2022)
//------------------------------------------------
#include <Arduino.h>
#include <MAX7219_7Seg_Disp.h>
//========================================================================
// Constructor
//========================================================================
MAX7219_7Seg_Disp::MAX7219_7Seg_Disp(int DIN, int CS, int CLK)
{
  pinMode(DIN, OUTPUT); _DIN = DIN;
  pinMode(CS, OUTPUT); _CS = CS;
  pinMode(CLK, OUTPUT); _CLK = CLK;
}
byte temp;
//========================================================================
// Public Methods
//========================================================================
void MAX7219_7Seg_Disp::Initialize(byte brightLevel)
{
  Write(0x0A, brightLevel);               //brightness level (0->15)
  Write(0x0B, 7);                         //scan limit: all digits ON
  Write(0x0C, 1);                         //turn ON MAX7219
}
//========================================================================
void MAX7219_7Seg_Disp::Clear()
{
  temp = 0;
  Write(0x09, temp);
  for(byte i=1; i<=8; i++) Write(i, 0);
}
//========================================================================
void MAX7219_7Seg_Disp::Number(byte digit, byte n)
{
  switch(digit)
  {
    case 1: temp |= 0b00000001; break;
    case 2: temp |= 0b00000010; break;
    case 3: temp |= 0b00000100; break;
    case 4: temp |= 0b00001000; break;
    case 5: temp |= 0b00010000; break;
    case 6: temp |= 0b00100000; break;
    case 7: temp |= 0b01000000; break;
    case 8: temp |= 0b10000000;
  }
  //---------------------------------
  Write(0x09, temp);
  Write(digit, n);
}
//========================================================================
void MAX7219_7Seg_Disp::Numberdp(byte digit, byte n)
{
  byte cb;
  switch(n)
  {
    case 0: cb = 0xFE; break;
    case 1: cb = 0xB0; break;
    case 2: cb = 0xED; break;
    case 3: cb = 0xF9; break;
    case 4: cb = 0xB3; break;
    case 5: cb = 0xDB; break;
    case 6: cb = 0xDF; break;
    case 7: cb = 0xF0; break;
    case 8: cb = 0xFF; break;
    case 9: cb = 0xFB;
  }
  //---------------------------------
  Write(0x09, temp);
  Write(digit, cb);
}
//========================================================================
void MAX7219_7Seg_Disp::Char(byte digit, char c)
{
  byte cb;
  switch(c)
  {
    case 'A': cb = 0x77; break;
    case 'B': cb = 0x1F; break;
    case 'C': cb = 0x4E; break;
    case 'D': cb = 0x3D; break;
    case 'E': cb = 0x4F; break;
    case 'F': cb = 0x47; break;
    case 'G': cb = 0x7B; break;
    case 'H': cb = 0x37; break;
    case 'I': cb = 0x06; break;
    case 'J': cb = 0x3C; break;
    case 'L': cb = 0x0E; break;
    case 'N': cb = 0x15; break;
    case 'O': cb = 0x1D; break;
    case 'P': cb = 0x67; break;
    case 'R': cb = 0x05; break;
    case 'S': cb = 0x5B; break;
    case 'T': cb = 0x0F; break;
    case 'U': cb = 0x1C; break;
    case 'Y': cb = 0x3B; break;
    case '=': cb = 0x09; break;
    case ' ': cb = 0;
  }
  //---------------------------------
  Write(0x09, temp);
  Write(digit, cb);
}
//========================================================================
// Private Methods
//========================================================================
void MAX7219_7Seg_Disp::Write(byte cmd, byte data)
{
  digitalWrite(_CS, LOW);                   //CS low
  //-------------------------------------------------
  SPI_send(cmd);
  SPI_send(data);
  //-------------------------------------------------
  digitalWrite(_CS, HIGH);                  //CS high
}
//========================================================================
void MAX7219_7Seg_Disp::SPI_send(byte data)
{
  for(byte i=0; i<8; i++)
  {
    digitalWrite(_CLK, LOW);                //CLK low
    //-------------------------------------------------------------
    if(data & 0x80) digitalWrite(_DIN, HIGH);//o/p high if MSB = 1
    else digitalWrite(_DIN, LOW);           //o/p low if MSB = 0
    //--------------------------------------------------------------
    digitalWrite(_CLK, HIGH);               //CLK high
    data = data << 1;                       //shift data left one bit
  }  
}