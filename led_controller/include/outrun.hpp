#ifndef OUTRUN_H
#define OUTRUN_H

#include <Adafruit_NeoPixel.h>
#include "led.hpp"

#define OUTRUN_NODES 5
#define NUM_COLORS 4
#define STEP LENGTH / (OUTRUN_NODES - 1);

typedef struct outrun_struct {
	Color colors[NUM_COLORS];
	long switch_length;
	long update_length;
	int node_locations[OUTRUN_NODES];
	Color node_colors[OUTRUN_NODES][2];
	uint8_t node_switch[OUTRUN_NODES];
} OutrunSet;

extern OutrunSet *outrun_set;

void outrun_init();
void drive();

static Color combine(Color one, Color two, int dist_one, int dist_two);

#endif
