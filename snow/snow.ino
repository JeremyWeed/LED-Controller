
#include <Adafruit_NeoPixel.h>

#define PIN 8  //Pin on teensy used to control the strip
#define LENGTH 147 //number of leds in the strip

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LENGTH, PIN, NEO_GRB + NEO_KHZ800);

int e = 0;
unsigned int a_snow[LENGTH];
bool b_snow[LENGTH];
char brightness = 255;
int max_lit = 252;



void setup() {
  randomSeed(analogRead(0));
  leds.begin();
}

void loop() {

  snow();
}

//uses two arrays to create what should feel like a "snowing" effect on the strip
//randomly chooses an led, brightens it quickly, then slowly lets it fade
void snow() {

  if (e > 8) {
    e = 0;
    b_snow[random(LENGTH)] = true;  //choose an led to light
  }
  e++;
  for (int i = 0; i < LENGTH; i++) {

    if (b_snow[i] == true) { //brighten the led

      if (a_snow[i] >= max_lit) {
        b_snow[i] = false;
      } else {
        a_snow[i] += 3;
      }

    } else if (a_snow[i] > 0) { //darken the light
      a_snow[i]--;
    }

    leds.setPixelColor(i, a_snow[i],
                       a_snow[i], a_snow[i]);
    //sets led to pure white
  }
  leds.show();
  delay(15);  //slow the loop down a bit
}

  

