// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>

#define PIN        4 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 12 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int loc[2] = {5,5};
void automata(Adafruit_NeoPixel *strip, uint32_t color, int *loc, unsigned char key, int axis=0){
  //automata(&pixels, magenta, loc, 54, 0);
  int depth = 200;
  int width = 51;
  
  int array[width*2];
  int *a = &array[0];
  int *b = &array[width];
  int *c;


  int i,j,k;
  for(j = 0; j < width; j++){
    a[j] = 0;
    if(j == 0 || j == width-1) a[j] = 1;
    else if(j == width/2 || j == width/2+2) a[j] = 1;
    else if(j == width/2+1) a[j] = 1;
    //a[j] = BoolRNG();
  }

  int seq[8];
  for(i = 0; i < 8; i++){
    seq[i] = (key >> (7-i)) & 0x1;
  }

  long start = millis();

  while(millis() - start < 2000){
    if(a[loc[!axis]] > 0){
      for(i = 1; i < a[loc[!axis]]; i++){
        
        b[0] = seq[7 - (a[width-1]*4 + a[0]*2 + a[1])];
        for(j = 1; j < width-1; j++){ b[j] = seq[7 - (a[j-1]*4 + a[j]*2 + a[j+1])]; }
        b[width-1] = seq[7 - (a[width-2]*4 + a[width-1]*2 + a[0])];
    
        c = a;
        a = b;
        b = c;
        
      }
    }
  }

  for(i = 1; i < depth; i++){

    /*
    for(j = 0 - 5; j < width; j++){
      if(a[j] != 0) Serial.print('#');
      else Serial.print(' ');
    }
    Serial.println();
    */
    
    if(a[loc[axis]]) strip->fill(color);
    else strip->clear();
    strip->show(); 

    b[0] = seq[7 - (a[width-1]*4 + a[0]*2 + a[1])];
    for(j = 1; j < width-1; j++){ b[j] = seq[7 - (a[j-1]*4 + a[j]*2 + a[j+1])]; }
    b[width-1] = seq[7 - (a[width-2]*4 + a[width-1]*2 + a[0])];

    c = a;
    a = b;
    b = c;

    // Display delay
    start = millis();
    while(millis()-start < 100){}
  }
}

void setup() {
  Serial.begin(115200);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  uint32_t magenta = pixels.Color(255, 0, 255);
  automata(&pixels, magenta, loc, 54, 0);
/*
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels.show();   
    delay(500);
  }
  */
}
