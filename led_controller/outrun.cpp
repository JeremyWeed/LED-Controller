// Implements functions in outrun.hpp

#include "include/outrun.hpp"

OutrunSet *outrun_set;

void outrun_init() {

	outrun_set = (OutrunSet*) calloc(1, sizeof(OutrunSet));
	OutrunSet *os = outrun_set;

	setCol(&os->cols[0], 0x07d8cf); // blue
	setCol(&os->cols[1], 0xea0ab3); // pink
	setCol(&os->cols[2], 0xf7a481); // orange/yellow
	setCol(&os->cols[3], 0x170562); // dark blue

	os->length = 10000; // ms

	unsigned char step = LENGTH / (OUTRUN_NODES - 1);
	for (int i = 0; i < OUTRUN_NODES - 1; i++){
		os->node_locations[i] = i * step;
	}
	// Doing this to watch out for integer division errors
	os->node_locations[OUTRUN_NODES - 1] = LENGTH - 1;

	for (int i = 0; i < OUTRUN_NODES; i++) {
		os->node_colors[i] = os->cols[0];
	}
}

void drive() {
	static unsigned long last_loop = 0;
	last_loop = millis();

	// Change the color of one node
	os->node_colors[random(OUTRUN_NODES)] = cols[random(NUM_COLORS)];

	unsigned char node = 1;
	for (int i = 0; i < LENGTH; i++) {
		if (i == os->node_locations[node]) {
			leds.setPixelColor(i,
							   os->node_colors[node].R,
							   os->node_colors[node].G,
							   os->node_colors[node].B);
			node += 1;
		} else {
			Color col = combine(os->node_colors[node - 1], os->node_colors[node],
								i - os->node_locations[node - 1],
								os->node_locations[node] - i);
			leds.setPixelColor(i, col.R, col.G, col.B);
		}
	}
	if (last_loop + outrun_set->length > millis()){
		delay(last_loop - millis() + outrun_set->length);
	}
	leds.show();
}

static Color combine(Color one, Color two, int dist_one, int dist_two) {
	Color ret;
	ret.R = (one.R * dist_one + two.R * dist_two) / (dist_one + dist_two);
	ret.G = (one.G * dist_one + two.G * dist_two) / (dist_one + dist_two);
	ret.B = (one.B * dist_one + two.B * dist_two) / (dist_one + dist_two);
	return ret;
}
