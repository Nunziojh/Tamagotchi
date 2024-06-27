#include <stdio.h>
#include <string.h>
#include "lpc17xx.h"
#include "../GLCD/GLCD.h"
#include "../timer/timer.h"
#include "../RIT/RIT.h"
#include "../TouchPanel/TouchPanel.h"
#include "../adc/adc.h"

extern volatile unsigned int c_happ, c_sat,vivo;
extern volatile float volume;
extern const uint16_t vol1[],vol2[],vol3[];

void refill_happiness();
void refill_satiety();
void snack();
void meal();
void sadness();
void hungry();
void Draw_Pet(int x_s, int y_s,const uint16_t *pica_pick,int w, int h);
int get_vivo();
void set_vivo(int i);
float get_volume();
void set_volume(float i);
void Draw_volume(int i);