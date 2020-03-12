/*
ESP8266 Blink
Blink the blue LED on the ESP8266 module
*/
#include "bitmap.h"
//#define LED 2 //Define blinking LED pin

#include <Adafruit_NeoPixel.h>

#define LED_PIN   D4
#define LED_COUNT 12

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(200); // Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.begin(115200);
  Serial.println("Hello, you've entered setup()...");
  
  bitmap bm = bitmap(15,5,&strip);
  bm.generate_msg_v("UcLa RoCkS!");
//  bm.generate_sequence_v(0, 14);
//  bm.generate_sequence_v(1, 14);
//  bm.generate_sequence_v(2, 14);
//  bm.generate_sequence_v(3, 14);
//  bm.generate_sequence_v(4, 14);

  // Add these to the bitmap class? Enums??
  uint32_t red = strip.Color(150,0,0);
  uint32_t green = strip.Color(0,150,0);
  uint32_t blue = strip.Color(0,0,150);
  uint32_t yellow = strip.Color(200,130,0);

  bm.print_scroll();
//  for (int r = 0; r < 5; ++r) {
//    for (int c = 0; c < 5; ++r) {
//      bm.show_location(r, c, blue, 10);
//      Serial.print("Showed location!");
//    }
//  }

  Serial.println("Woohoo! Still works :D");
}
// the loop function runs over and over again forever
void loop() {

}
