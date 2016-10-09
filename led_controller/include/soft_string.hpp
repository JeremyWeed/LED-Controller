//header file for the soft string light
#include "led.hpp"


typedef struct SoftSet{
	bool cur_lit[LENGTH];
	unsigned char curBright[LENGTH];
	unsigned long curStay[LENGTH];

	Color col;

	unsigned char brightness;

	unsigned long tIncrease;
	unsigned long tDecrease;
	unsigned long tStay;
	unsigned long tChoose;
	

}SoftSet;

extern SoftSet *soft_set;

void soft_string_init();
void soft_light();
void change_soft_color(Color col);
