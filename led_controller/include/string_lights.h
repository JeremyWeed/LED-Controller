#ifndef STRING_LIGHTS
#define STRING_LIGHTS

#include "led.h"

#define NUM_COLORS 5

typedef struct LightSet{

	unsigned char cur_lit[LENGTH];
	bool incre[LENGTH];

	Color cols[NUM_COLORS];
	Color cur_c[LENGTH];

	unsigned long in_len;
	unsigned long de_len;
	unsigned long ch_len;

}LightSet;

extern LightSet *light_set;

void sl_init();
void string_light_main();
void choose_color(int i);

#endif