#include "led.hpp"

typedef struct SnowSet{

	unsigned char cur_lit[LENGTH];
	bool cur_b[LENGTH];

	Color col;

	unsigned char max_lit;

	unsigned long in_length;
	unsigned long de_length;
	unsigned long ch_length;

}SnowSet;

extern SnowSet *snow_set;

void s_init();
void snow();
void change_snow_color(Color col);
