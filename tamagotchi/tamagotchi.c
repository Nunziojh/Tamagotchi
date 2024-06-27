#include "tamagotchi.h"


/*funzione per la stampa  delle  immagini*/
void Draw_Pet(int x_s, int y_s,const uint16_t *pick, int w, int h){
	int x,y,i=0;
	for (x=0;x<h;x++){
		for (y=0;y<w;y++){
			LCD_SetPoint(x_s+y, y_s+x, pick[i++]);
		}
	}
}
/*funzione per l'incremento del contatore felicita' e del disegno delle batterie*/
void snack(){
	disable_RIT();
	if(c_happ == 0){
		c_happ++;
		LCD_DrawRectangle(14,49,15,22,Black);
	}else if(c_happ == 1){
		c_happ++;
		LCD_DrawRectangle(31,49,15,22,Black);
	}else if(c_happ == 2){
		c_happ++;
		LCD_DrawRectangle(48,49,15,22,Black);
	}else if(c_happ == 3){
		c_happ++;
		LCD_DrawRectangle(65,49,15,22,Black);
	}
	enable_RIT();
}
/*funzione per l'incremento del contatore sazieta' e del disegno delle batterie*/
void meal(){
	disable_RIT();
	if(c_sat == 0){
		c_sat++;
		LCD_DrawRectangle(159,49,15,22,Black);
	}else if(c_sat == 1){
		c_sat++;
		LCD_DrawRectangle(176,49,15,22,Black);
	}else if(c_sat == 2){
		c_sat++;
		LCD_DrawRectangle(193,49,15,22,Black);
	}else if(c_sat == 3){
		c_sat++;
		LCD_DrawRectangle(210,49,15,22,Black);
	}
	enable_RIT();
}
/*funzione per la diminuzione del contatore felicita' e del disegno delle batterie*/
void sadness(){
	disable_RIT();
	if(c_happ == 1){
		c_happ--;
		LCD_DrawRectangle(14,49,15,22,White);
	}else if(c_happ == 2){
		c_happ--;
		LCD_DrawRectangle(31,49,15,22,White);
	}else if(c_happ == 3){
		c_happ--;
		LCD_DrawRectangle(48,49,15,22,White);
	}else if(c_happ == 4){
		c_happ--;
		LCD_DrawRectangle(65,49,15,22,White);
	}
	enable_RIT();
}
/*funzione per la diminuzione del contatore sazieta' e del disegno delle batterie*/
void hungry(){
	disable_RIT();
	if(c_sat == 1){
		c_sat--;
		LCD_DrawRectangle(159,49,15,22,White);
	}else if(c_sat == 2){
		c_sat--;
		LCD_DrawRectangle(176,49,15,22,White);
	}else if(c_sat == 3){
		c_sat--;
		LCD_DrawRectangle(193,49,15,22,White);
	}else if(c_sat == 4){
		c_sat--;
		LCD_DrawRectangle(210,49,15,22,White);
	}
	enable_RIT();
}
/*funzione per riempire la batteria della felicita'*/
void refill_happiness(){
	int i;
	for(i=0;i<4;i++){
		snack();
	}
}
/*funzione per riempire la batteria della sazieta'*/
void refill_satiety(){
	int i=0;
	for(i=0;i<4;i++){
		meal();
	}
}
/*getter di vivo*/
int get_vivo(){
	return vivo;
}
/*setter di vivo*/
void set_vivo(int i){
	vivo = i;
}
/*getter di volume*/
float get_volume(){
	return volume;
}
/*setter di volume*/
void set_volume(float i){
	volume=i;
}
/*funzione per gestire le stampe del volume*/
void Draw_volume(int i){
	if(i==0){
		LCD_DrawRectangle(225,8,3,11,White);
		LCD_DrawRectangle(228,7,4,13,White);
		LCD_DrawRectangle(232,6,4,15,White);
	}else if(i==1){
		Draw_Pet(225,8,vol1,3,11);
		LCD_DrawRectangle(228,7,4,13,White);
		LCD_DrawRectangle(232,6,4,15,White);
	}else if (i==2){
		Draw_Pet(225,8,vol1,3,11);
		Draw_Pet(228,7,vol2,4,13);
		LCD_DrawRectangle(232,6,4,15,White);
	}else if(i == 3){
		Draw_Pet(225,8,vol1,3,11);
		Draw_Pet(228,7,vol2,4,13);
		Draw_Pet(232,6,vol3,4,15);
	}
	
}