//------------------------------------------------
// MAX7219_7Seg_Disp.h - Header File
// Library for Displaying Numbers & Chracters on
// MAX7219 8-Digit 7-Segment Display
// by: Anas Kuzechie (June, 2022)
//------------------------------------------------
//header guards
#ifndef MAX7219_7Seg_Disp_h
#define MAX7219_7Seg_Disp_h
//--------------------------------------------------------
//class definition
class MAX7219_7Seg_Disp
{
    public:
        //constructor
        MAX7219_7Seg_Disp(int DIN, int CS, int CLK);
        //methods
        void Initialize(byte brightLevel);
        void Clear();
        void Number(byte digit, byte n);
        void Numberdp(byte digit, byte n);
        void Char(byte digit, char c);
    private:
        int _DIN;
        int _CS;
        int _CLK;
        void Write(byte cmd, byte data);
        void SPI_send(byte data);
};
//--------------------------------------------------------
#endif