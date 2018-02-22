// Implements functions in outrun.hpp

#include "include/outrun.hpp"

OutrunSet *outrun_set;

void outrun_init() {

	outrun_set = (OutrunSet*) calloc(1, sizeof(OutrunSet));
	OutrunSet *os = outrun_set;

	setCol(&os->colors[0], 0x07d8cf); // blue
	setCol(&os->colors[1], 0xea0ab3); // pink
	setCol(&os->colors[2], 0xf7a481); // orange/yellow
	setCol(&os->colors[3], 0x170562); // dark blue

	os->switch_length = 10000; // ms
	os->update_length = 100;

	for (int i = 0; i < OUTRUN_NODES - 1; i++){
		os->node_locations[i] = i * STEP;
	}
	// Doing this to watch out for integer division errors
	os->node_locations[OUTRUN_NODES - 1] = LENGTH - 1;

	for (int i = 0; i < OUTRUN_NODES; i++) {
		os->node_colors[i][0]	= os->colors[0];
		os->node_colors[i][1]	= os->colors[0];
		os->node_switch[i]		= 255;
	}
}

void drive() {
	static unsigned long last_update = 0;
	static unsigned long last_switch = 0;
	static Color node_cur_color[OUTRUN_NODES];
	static OutrunSet *os = outrun_set;
	/* last_loop = millis(); */

	// Change the color of one node
	if (os->switch_length + last_switch < millis()) {
		int i = random(OUTRUN_NODES);
		// don't reset the colors until we chose one that's done switching
		if (os->node_switch[i] == 255){
			os->node_colors[i][0] = os->node_colors[i][1];
			os->node_colors[i][1] = os->colors[random(NUM_COLORS)];
			os->node_switch[i] = 0;
			last_switch = millis();
		}
	}
	// update the colors
	if (os->update_length + last_update < millis()) {
		last_update = millis();

		for (int i = 0; i < OUTRUN_NODES; i++) {

			os->node_switch[i] = (os->node_switch[i] < 255) ? os->node_switch[i] + 1 : 255;

			node_cur_color[i] = combine(os->node_colors[i][0], os->node_colors[i][1],
										os->node_switch[i],    255-os->node_switch[i]);
		}
		for (int i = 0; i < LENGTH; ++i) {
			int left = i / STEP;

			Color col = combine(node_cur_color[i], node_cur_color[i+1],
								i - os->node_locations[left], os->node_locations[i+1] - i);
			leds.setPixelColor(i, col.R, col.G, col.B);
		}
	}
	leds.show();
}

static Color combine(Color one, Color two, int dist_one, int dist_two) {
	Color ret;
	ret.R = (one.R * dist_two + two.R * dist_one) / (dist_one + dist_two);
	ret.G = (one.G * dist_two + two.G * dist_one) / (dist_one + dist_two);
	ret.B = (one.B * dist_two + two.B * dist_one) / (dist_one + dist_two);
	return ret;
}
