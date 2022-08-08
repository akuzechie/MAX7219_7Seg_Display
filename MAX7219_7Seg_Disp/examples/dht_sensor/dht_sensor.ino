//------------------------------------------------
// DHT Sensor: Temp & Humidity on MAX7219 Display
// using MAX7219_7Seg_Disp.h Library
// by: Anas Kuzechie
//------------------------------------------------
#include <MAX7219_7Seg_Disp.h>
#include <DHT.h>
//-------------------------------------------------------
                    /*DIN  CS  CLK*/
MAX7219_7Seg_Disp disp(2,  3,  4);
DHT dht(5, DHT22);  /*DHT22 or DHT11 connected to pin 5*/
//-------------------------------------------------------
float temperature, humidity;
int temp_LSD, temp_MSD, temp_fraction, hum_LSD, hum_MSD, hum_fraction;
//====================================================================
void setup()
{
  dht.begin();
  disp.Initialize(1);  /*initialize MAX7219 & set brightness level*/
  disp.Clear();        /*clear all 8 digits of display*/
}
//====================================================================
void loop()
{
  delay(2000);
  //--------------------------------------------------
  temperature = dht.readTemperature();
  temp_MSD = int(temperature)/10;
  temp_LSD = int(temperature)%10;
  temp_fraction = (temperature - int(temperature))*10;
  //--------------------------------------------------
  disp.Number  (8, temp_MSD);
  disp.Numberdp(7, temp_LSD);
  disp.Number  (6, temp_fraction);
  disp.Char    (5, 'C');
  //--------------------------------------------------
  humidity = dht.readHumidity();
  hum_MSD = int(humidity)/10;
  hum_LSD = int(humidity)%10;
  hum_fraction = (humidity - int(humidity))*10;
  //--------------------------------------------------
  disp.Number  (4, hum_MSD);
  disp.Numberdp(3, hum_LSD);
  disp.Number  (2, hum_fraction);
  disp.Char    (1, 'H');
}