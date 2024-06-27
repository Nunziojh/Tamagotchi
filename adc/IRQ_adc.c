/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../timer/timer.h"

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

unsigned short AD_current;   
unsigned short AD_last = 0xFF;     /* Last converted value               */
extern volatile unsigned int volume;
extern float get_volume();
extern void set_volume(float i);
extern void Draw_volume(int i);
/* k=1/f'*f/n  k=f/(f'*n) k=25MHz/(f'*45) */

//const int freqs[8]={4240,3779,3367,3175,2834,2525,2249,2120};
/* 
131Hz		k=4240 C3
147Hz		k=3779
165Hz		k=3367
175Hz		k=3175
196Hz		k=2834		
220Hz		k=2525
247Hz		k=2249
262Hz		k=2120 C4
*/

const int freqs[19]={5351,4500,4370,4240,3779,3367,3175,2834,2670,2525,2249,2120,1890,1684,1592,1417,1263,1125,1062};
/*		47750, 50500, 4500,	 4370,	53750, 56750, 60250, 63750, 67500, 71750, 75750, 80500, 85000, 90250, 95500
			2120,1890,1684 4370,4240,	,1592,1417,1263,1125,1062
	a2b = 5351,	// 1034240,	3779,	Hz	k=5351 a2b
	b2 = 4500,	// 1233779,	3367,	Hz	k=4500 b2
	c3b = 4370,	// 1273367,	3175,	Hz	k)4370 c3b
	c3 = 4240,	// 1313175,	2834,	Hz	k=4240 c3
	d3 = 3779,	// 1472834,	 2670, Hz	k=3779 d3
	e3 = 3367,	// 165 2670,2525,	Hz	k=3367 e3
	f3 = 3175,	// 1752525,	2249,	Hz	k=3175 f3
	g3 = 2834,	// 1962249,	2120,	Hz	k=2834 g3
	a3b = 2670, // 2082120,	1890,	Hz  k=2670 a4b
	a3 = 2525,	// 2201890,	1684,	Hz	k=2525 a3
	b3 = 2249,	// 2471684,	1592,	Hz	k=2249 b3
	c4 = 2120,	// 2621592,	1417,	Hz	k=2120 c4
	d4 = 1890,	// 2941417,	1263,	Hz	k=1890 d4
	e4 = 1684,	// 3301263,	1125,	Hz	k=1684 e4
	f4 = 1592,	// 3491125,	1062, 	Hz	k=1592 f4
	g4 = 1417,	// 3921062, Hz	k=1417 g4
	a4 = 1263,	// 440Hz	k=1263 a4
	b4 = 1125,	// 494Hz	k=1125 b4
	c5 = 1062, 	// 523Hz	k=1062 c5

262Hz	k=2120		c4
294Hz	k=1890		
330Hz	k=1684		
349Hz	k=1592		
392Hz	k=1417		
440Hz	k=1263		
494Hz	k=1125		
523Hz	k=1062		c5

*/

void ADC_IRQHandler(void) {
  /* Read Conversion Result*/
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);
	/*movimento del potenziometro*/
  if(AD_current != AD_last){
		
		if(AD_current<0xFFF/4){ //volume 0
			set_volume(0);
			Draw_volume(0);
		}else if(AD_current<0xFFF/2){ //volume 1
			set_volume(3.5);
			Draw_volume(1);
		}else if(AD_current<((3*0xFFF)/4)){ //volume 2
			set_volume(3.8);
			Draw_volume(2);
		}else if(AD_current<0xFFF){ //volume 3
			set_volume(4.5);
			Draw_volume(3);
		}
		
		AD_last = AD_current;
  }
	
}
