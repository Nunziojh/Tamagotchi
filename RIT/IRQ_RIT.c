/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../GLCD/GLCD.h"
#include "../timer/timer.h"
#include "../TouchPanel/TouchPanel.h"ù
#include "../adc/adc.h"


//#include "led/led.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/



extern const uint16_t pica_pick1[], pica_pick2[];
extern void Draw_Pet(int x_s, int y_s,const uint16_t *pica_pick, int w, int h);
extern int get_vivo(), pos;
extern void set_vivo(int i);
extern void snack();
extern void meal();
volatile int position=-1;
extern volatile unsigned int sec, min, ore, dec_h, dec_s,c_happ, c_sat, merenda, pasto,entrato,start,vivo,stop_rit;

void RIT_IRQHandler (void)
{	
	/* ADC management */
	ADC_start_conversion();
	
	if(stop_rit){
		LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
		return;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){
		/* Joystick Left pressed p1.27*/
		if(get_vivo()){
			/*stampa della scelta nel menu'*/
			LCD_DrawLine(0,290,120,290,Red);
			LCD_DrawLine(120,290,120,319,Red);
			LCD_DrawLine(120,319,0,319,Red);
			LCD_DrawLine(0,319,0,290,Red);
			LCD_DrawLine(120,290,239,290,0x0000);
			LCD_DrawLine(239,290,239,319,0x0000);
			LCD_DrawLine(120,319,239,319,0x0000);
			position = 0;
		}
	}else if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){
		/* Joystick Right pressed p1.28*/
		if(get_vivo()){
			/*stampa della scelta nel menu'*/
			LCD_DrawLine(120,290,120,319,Red);
			LCD_DrawLine(120,319,239,319,Red);
			LCD_DrawLine(239,319,239,290,Red);
			LCD_DrawLine(239,290,120,290,Red);
			LCD_DrawLine(0,290,120,290,Black);
			LCD_DrawLine(120,319,0,319,Black);
			LCD_DrawLine(0,319,0,290,Black);
			position = 1;
		}
	}
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){
		/* Joystick Select pressed p1.25*/
		if(vivo){
			/*scelta del menu' se il pet e' in vita*/
			if(position==0){
				/*snack*/
				merenda = 1;
				position = -1;
			}else if(position==1){
				/*meal*/
				pasto = 1;
				position = -1;
			}
		}else{
			/*tasto reset*/
			/*rinascita se il pet e' morto*/
			vivo=1;
			start=1;
			LCD_Clear(White);
			sec=0;min=0;ore=0;
			pos=0;
			dec_h=0;dec_s=0;
			c_happ=0;c_sat=0;
			disable_timer(3);
			reset_timer(3);
		}
	}
	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	//reset_RIT();
}

/******************************************************************************
**                            End Of File
******************************************************************************/
