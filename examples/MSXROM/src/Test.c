/* =============================================================================
  Test VDP_VPRINT Library
  Version: 1.2 (10 September 2020)
  Author: mvac7 [mvac7303b@gmail.com]
  Architecture: MSX
  Format: ROM
  Programming language: C
    
  Description:
  
   
  History of versions:
    - v1.2 (10 September 2020)
    - v1.1 (09 September 2020)
    - v1.0 (03 February 2016)
============================================================================= */

#include "../include/newTypes.h"
#include "../include/msxSystemVariables.h"
#include "../include/msxBIOS.h"

#include "../include/VDP_TMS9918A.h"
#include "../include/VDP_PRINT.h"



#define  HALT __asm halt __endasm   //wait for the next interrupt



// Definitions of Labels -------------------------------------------------------





// definition of functions  ----------------------------------------------------

void test_SC1();
void test_SC2();
void test();

void TwoSeconds();

void WAIT(uint cicles);
char INKEY();



// constants  ------------------------------------------------------------------

const char text01[] = "Test VDP PRINT library v1.2";
const char text02[] = "VDP_PRINT Lib v1.1";



// Project: mvac7_font_v0.2
// tileset pattern
// Tiles range: 0 to 125
// Size= 1008
const unsigned char TILESET_FONT[]={
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8F,0x81,0xBD,0xBD,0xBD,0x81,0xFF,
0x87,0xB3,0xB1,0xBD,0xBD,0xBD,0x81,0xFF,0x80,0x80,0x80,0xBE,0x80,0x80,0x80,0xFF,
0x80,0x88,0x88,0xBE,0x88,0x88,0x80,0xFF,0x80,0x80,0x80,0xBE,0x9C,0x88,0x80,0x80,
0x5C,0x62,0x70,0x5E,0x42,0x42,0x7E,0x00,0xFC,0xBA,0xBA,0x82,0x82,0x82,0xFE,0x00,
0x00,0x00,0x08,0x1C,0x3E,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x1C,0x08,0x00,0x00,
0x00,0x08,0x18,0x38,0x18,0x08,0x00,0x00,0x00,0x10,0x18,0x1C,0x18,0x10,0x00,0x00,
0x00,0x00,0x1C,0x22,0x22,0x22,0x1C,0x00,0x00,0x00,0x1C,0x3E,0x3E,0x3E,0x1C,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x0C,0x0C,0x0C,0x3F,0x0C,0x0C,0x0C,0x0C,0x18,0x18,0x18,0x7F,0x7F,0x00,0x00,0x00,
0x00,0x00,0x00,0xFF,0xFF,0x18,0x18,0x18,0x18,0x18,0x18,0xF8,0xF8,0x18,0x18,0x18,
0x18,0x18,0x18,0x1F,0x1F,0x18,0x18,0x18,0x18,0x18,0x18,0xFF,0xFF,0x18,0x18,0x18,
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x0F,0x1F,0x18,0x18,0x18,0x00,0x00,0x00,0xF0,0xF8,0x18,0x18,0x18,
0x18,0x18,0x18,0x1F,0x0F,0x00,0x00,0x00,0x18,0x18,0x18,0xF8,0xF0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0xFF,0xFF,0x08,0x08,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x00,0x18,0x00,
0x28,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x28,0x7C,0x28,0x7C,0x28,0x00,
0x10,0x7C,0xD0,0x7C,0x16,0x16,0x7C,0x10,0x00,0xC6,0xCC,0x18,0x30,0x66,0xC6,0x00,
0x00,0x70,0xD8,0x7A,0xCC,0xCC,0x7A,0x00,0x18,0x30,0x00,0x00,0x00,0x00,0x00,0x00,
0x18,0x30,0x60,0x60,0x60,0x30,0x18,0x00,0x60,0x30,0x18,0x18,0x18,0x30,0x60,0x00,
0x00,0x00,0x54,0x38,0x7C,0x38,0x54,0x00,0x00,0x00,0x30,0x30,0xFC,0x30,0x30,0x00,
0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x20,0x00,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x06,0x0C,0x18,0x30,0x60,0xC0,0x00,
0x7C,0xC6,0xCE,0xD6,0xE6,0xC6,0x7C,0x00,0x30,0x70,0x30,0x30,0x30,0x30,0x78,0x00,
0xFC,0x06,0x06,0x7C,0xC0,0xC0,0xFE,0x00,0xFC,0x06,0x06,0x7C,0x06,0x06,0xFC,0x00,
0xC6,0xC6,0xC6,0xFE,0x06,0x06,0x06,0x00,0xFE,0xC0,0xC0,0xFC,0x06,0x06,0xFC,0x00,
0x7C,0xC0,0xC0,0xFC,0xC6,0xC6,0x7C,0x00,0xFE,0x06,0x0C,0x18,0x30,0x30,0x30,0x00,
0x7C,0xC6,0xC6,0x7C,0xC6,0xC6,0x7C,0x00,0x7C,0xC6,0xC6,0x7E,0x06,0x06,0x7C,0x00,
0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x00,0x00,0x30,0x30,0x00,0x30,0x30,0x20,0x00,
0x00,0x00,0x18,0x30,0x60,0x30,0x18,0x00,0x00,0x00,0x00,0x78,0x00,0x78,0x00,0x00,
0x00,0x00,0x60,0x30,0x18,0x30,0x60,0x00,0x3C,0x66,0x06,0x0C,0x18,0x00,0x18,0x00,
0x7C,0x82,0xBA,0xAA,0xBE,0x80,0x7C,0x00,0x7C,0xC6,0xC6,0xC6,0xFE,0xC6,0xC6,0x00,
0xFC,0xC6,0xC6,0xFC,0xC6,0xC6,0xFC,0x00,0x7E,0xC0,0xC0,0xC0,0xC0,0xC0,0x7E,0x00,
0xFC,0xC6,0xC6,0xC6,0xC6,0xC6,0xFC,0x00,0xFE,0xC0,0xC0,0xF8,0xC0,0xC0,0xFE,0x00,
0xFE,0xC0,0xC0,0xFC,0xC0,0xC0,0xC0,0x00,0x7E,0xC0,0xC0,0xCE,0xC6,0xC6,0x7E,0x00,
0xC6,0xC6,0xC6,0xFE,0xC6,0xC6,0xC6,0x00,0x3C,0x18,0x18,0x18,0x18,0x18,0x3C,0x00,
0x3C,0x18,0x18,0x18,0x18,0xD8,0x70,0x00,0xC6,0xC6,0xCC,0xF8,0xCC,0xC6,0xC6,0x00,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xFE,0x00,0xC6,0xEE,0xFE,0xD6,0xC6,0xC6,0xC6,0x00,
0xC6,0xE6,0xF6,0xDE,0xCE,0xC6,0xC6,0x00,0x7C,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00,
0xFC,0xC6,0xC6,0xC6,0xFC,0xC0,0xC0,0x00,0x7C,0xC6,0xC6,0xC6,0xD6,0xCC,0x7A,0x00,
0xFC,0xC6,0xC6,0xFC,0xC6,0xC6,0xC6,0x00,0x7E,0xC0,0xC0,0x7C,0x06,0x06,0xFC,0x00,
0xFC,0x30,0x30,0x30,0x30,0x30,0x30,0x00,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00,
0xC6,0xC6,0xC6,0xC6,0xC6,0x6C,0x38,0x00,0xC6,0xC6,0xC6,0xD6,0xFE,0xEE,0xC6,0x00,
0xC6,0xC6,0x6C,0x38,0x6C,0xC6,0xC6,0x00,0xCC,0xCC,0xCC,0x78,0x30,0x30,0x30,0x00,
0xFE,0x06,0x0C,0x18,0x30,0x60,0xFE,0x00,0x1C,0x18,0x18,0x18,0x18,0x18,0x1C,0x00,
0x00,0xC0,0x60,0x30,0x18,0x0C,0x06,0x00,0x70,0x30,0x30,0x30,0x30,0x30,0x70,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x06,0x7E,0xC6,0xFE,0x00,
0xC0,0xC0,0xFC,0xC6,0xC6,0xC6,0xFC,0x00,0x00,0x00,0x7E,0xC0,0xC0,0xC0,0x7E,0x00,
0x06,0x06,0x7E,0xC6,0xC6,0xC6,0x7E,0x00,0x00,0x00,0x7C,0xC6,0xFE,0xC0,0x7C,0x00,
0x3C,0x60,0x60,0xF8,0x60,0x60,0x60,0x00,0x00,0x00,0x7E,0xC6,0xC6,0x7E,0x06,0x7C,
0xC0,0xC0,0xFC,0xC6,0xC6,0xC6,0xC6,0x00,0x18,0x00,0x38,0x18,0x18,0x18,0x3C,0x00,
0x18,0x00,0x18,0x18,0x18,0x18,0x18,0x70,0xC0,0xC0,0xC6,0xCC,0xF8,0xCC,0xC6,0x00,
0x70,0x30,0x30,0x30,0x30,0x30,0x78,0x00,0x00,0x00,0xFC,0xD6,0xD6,0xD6,0xD6,0x00,
0x00,0x00,0xFC,0xC6,0xC6,0xC6,0xC6,0x00,0x00,0x00,0x7C,0xC6,0xC6,0xC6,0x7C,0x00,
0x00,0x00,0xFC,0xC6,0xC6,0xC6,0xFC,0xC0,0x00,0x00,0x7E,0xC6,0xC6,0xC6,0x7E,0x06,
0x00,0x00,0xFC,0xC6,0xC0,0xC0,0xC0,0x00,0x00,0x00,0x7E,0xC0,0x7C,0x06,0xFC,0x00,
0x30,0x30,0x7C,0x30,0x30,0x30,0x1C,0x00,0x00,0x00,0xC6,0xC6,0xC6,0xC6,0x7C,0x00,
0x00,0x00,0xC6,0xC6,0xC6,0x6C,0x38,0x00,0x00,0x00,0xC6,0xD6,0xFE,0xEE,0xC6,0x00,
0x00,0x00,0xC6,0x6C,0x38,0x6C,0xC6,0x00,0x00,0x00,0xC6,0xC6,0xC6,0x7E,0x06,0x7C,
0x00,0x00,0xFC,0x18,0x30,0x60,0xFC,0x00,0x0C,0x18,0x18,0x30,0x18,0x18,0x0C,0x00,
0x30,0x30,0x30,0x00,0x30,0x30,0x30,0x00,0x60,0x30,0x30,0x18,0x30,0x30,0x60,0x00};







// Functions -------------------------------------------------------------------


//
void main(void)
{
     
  test_SC1();
 
  test_SC2();
  

//EXIT MSXDOS
/*  screen(0);
    
__asm
 	ld b,4(ix)
	ld c,#0x62
	call 5 
__endasm;*/
//end EXIT

  return;
}



/* =============================================================================
One character input (waiting)
============================================================================= */
char INKEY() __naked
{
__asm   
   call CHGET
   ld   L,A
   ret
__endasm;
}



// Generates a pause in the execution of n interruptions.
// PAL: 50 = 1 second. ; NTSC: 60 = 1 second. 
void WAIT(uint cicles)
{
  uint i;
  for(i=0;i<cicles;i++) HALT;
  return;
}



void TwoSeconds()
{
    WAIT(50*2);
}



// TEST 
void test_SC1()
{
  COLOR(LIGHT_GREEN,DARK_GREEN,DARK_GREEN);    
  SCREEN(1);
  //copy to VRAM tileset, only gfx patterns
  CopyToVRAM((uint) TILESET_FONT,BASE7,126*8);  

  VPRINT(24,23,"SCREEN 1");
  
  test();
  
  VPRINT(0,22,"Press any key");
  INKEY();  
 
  return;
}



void test_SC2()
{
  COLOR(15,4,14);    
  SCREEN(2);
  FillVRAM(BASE10,0x300,32);
  
  //copy to VRAM tileset,  gfx patterns
  CopyToVRAM((uint) TILESET_FONT,BASE12,126*8);
  CopyToVRAM((uint) TILESET_FONT,BASE12+BANK1,126*8);
  CopyToVRAM((uint) TILESET_FONT,BASE12+BANK2,126*8); 
  
  FillVRAM(BASE11,0x1800,0xF4); 
  
  VPRINT(24,23,"SCREEN 2");
  
  test();  
  
  VPRINT(0,22,"Press a key to exit");
  INKEY();  
 
  return;
}



void test()
{
  uint vaddr;
  
  VPRINT(0,0,text01);
  VPRINT(0,1,text02);  
  TwoSeconds();
    
  VPRINT(0,3,">Test VPRINT");
  TwoSeconds();
  VPRINT(3,4,"Alea iacta est");
  TwoSeconds();
  
  VPRINT(0,6,">Test VPRINTN [10 chars]");
  TwoSeconds();
  VPRINTN(3,7,"Alea iacta est",10);
  TwoSeconds();
  
  VPRINT(0,9,">test GetVRAMaddressByPosition()");
  TwoSeconds();
  vaddr = GetVRAMaddressByPosition(5,10);
  VPrintString(vaddr,"col=5, line=10");
  TwoSeconds();

/*en vez de utilizar coordenadas de pantalla, se puede calcular la posicion de
la VRAM y utilizar la funci�n VPrintString. Al no tener que calcular la direcci�n
la ejecucion sera m�s rapida*/   
  VPRINT(0,12,">test VPrintString()");
  TwoSeconds(); 
  vaddr = BASE10 + (13*32)+3;
  VPrintString(vaddr,"Ad infinitum");
  TwoSeconds();  
  
  VPRINT(0,15,">Test VPrintNumber(3,16,255,3)");
  TwoSeconds();
  VPrintNumber(3,16,255,3);
  TwoSeconds();  
  
  VPRINT(0,18,">Test VPrintNum(vaddr,1234,5)");
  TwoSeconds();
  vaddr = BASE10 + (19*32)+3;
  VPrintNum(vaddr,1234,5);
  TwoSeconds();

}