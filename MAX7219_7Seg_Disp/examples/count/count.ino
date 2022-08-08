//----------------------------------------
// Count form 0 to 9999 on MAX7219 Display
// using MAX7219_7Seg_Disp.h Library
// by: Anas Kuzechie
//----------------------------------------
#include <MAX7219_7Seg_Disp.h>
//-----------------------------
                    /*DIN  CS  CLK*/
MAX7219_7Seg_Disp disp(2,  3,  4);
//===================================================================
void setup()
{
  disp.Initialize(1);  /*initialize MAX7219 & set brightness level*/
  disp.Clear();        /*clear all 8 digits of display*/
  delay(1000);
}
//===================================================================
void loop()
{
  disp.Char(8, 'C');
  disp.Char(7, 'N');
  disp.Char(6, 'T');
  disp.Char(5, '=');
  //------------------------------------------------
  for(byte i=0; i<=9; i++)
  {
    disp.Number(4, i);
    for(byte j=0; j<=9; j++)
    {
      disp.Number(3, j);
      for(byte k=0; k<=9; k++)
      {
        disp.Number(2, k);
        for(byte l=0; l<=9; l++)
        {
          disp.Number(1, l);
          delay(map(analogRead(A5),0,1023,50,1000));
        }
      }
    }
  }
}