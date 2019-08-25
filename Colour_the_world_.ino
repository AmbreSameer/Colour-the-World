#include <Wire.h>                    // Library for I2C communication between colour sensor and arduino
#include "Adafruit_TCS34725.h"       //Library for Colour sensor we'll be using
#include <Adafruit_NeoPixel.h>       // Library for Neopixel Led Strip we'll using
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN    6                // Defining the pin number we use for programming Led Strip.

#define LED_COUNT 60                // Defining the count of leds present on strip

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);      // Activating the LED strip


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);     //Activating the colour sensor

void setup(void) {

  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  // Now we're ready to get readings!
}


void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  Serial.println(r); Serial.println(g); Serial.println(b); Serial.println("");


  if (r > 21000 && r < 26000 && g > 6000 && g < 10000 && b > 2500 && b < 7500 )       //detection of SAFFRON colour
  {
    Serial.println("Saffron is detected");
    colorWipe(strip.Color(255,   0,   70), 50);

  }



  else if (r > 2500 && r < 7500 && g > 12000 && g < 17000 && b > 3000 && b < 9000)   //detection of GREEN colour

  {
    Serial.println("Green is detected");
    colorWipe(strip.Color(0,  0,   255), 50);
  }

  else if (r > 1000 && r < 6000 && g > 3000 && g < 7000 && b > 10000 && b < 16000)   //detection of BLUE colour
  {
    Serial.println("Blue is detected");
    colorWipe(strip.Color(0,   255,   0), 50);
  }

  else if (r > 10000 && r < 15000 && g > 1000 && g < 4000 && b > 1000 && b < 6000 )  //detection of RED colour
  {
    Serial.println("Red is detected");
    colorWipe(strip.Color(255,   0,   0), 50);


  }
  else if (r > 10000 && r < 16000 && g > 4000 && g < 5000 && b > 4000 && b < 7000)  //detection of PINK colour
  {
    Serial.println("Pink is detected");
    colorWipe(strip.Color(255,   100,   0), 50);

  }

  else if (r > 26000 && r < 32000 && g > 23000 && g < 29000 && b > 10000 && b < 15000)  //detection of YELLOW colour
  {
    Serial.println("Yellow is detected");
    colorWipe(strip.Color(255,  0,   130), 50);
  }
  else
  {
    Serial.println("NO VALID COLOUR");
    colorWipe(strip.Color(0,  0,   0), 50);

  }

  delay(100);

}
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
