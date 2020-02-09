#include <ArduinoSTL.h>
#include<map>
#include <vector>
#include <Adafruit_NeoPixel.h>
#include <iostream>
#include <string>
#include <EEPROM.h>
#define LED_PIN    4
#define LED_COUNT 12
#define MY_ROLE 0
//#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember)) //This call doesn't work in Arduino
#define CALL_MEMBER_FN(object,ptrToMember, args)  ((object).*(ptrToMember))(args)
#define X_ADDR 0
#define Y_ADDR 1
#define MY_ROLE 2

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

class CommandHandler{
  typedef void (CommandHandler::*pfunc)(std::vector<String>&);
  
  CommandHandler::CommandHandler(){
    x = EEPROM.read(X_ADDR);
    y = EEPROM.read(Y_ADDR);
    role_id = MY_ROLE;
    init_commands_with_args();
  }
  CommandHandler::CommandHandler(int x, int y, int role_id){
    this->x = x;
    this->y = y;
    this->role_id = role_id;
    init_commands_with_args();
  }
  public:
    int x, y, role_id;
    std::map<String, pfunc> commandsTable; 
    void set_red(){show_led_int(255,0,0);}
    void set_green(){show_led_int(0,255,0);}
    void set_blue(){show_led_int(0,0,255);}
    void set_purple(){show_led_int(255, 0, 255);}
    void set_yellow(){show_led_int(255, 255, 0);}
    void set_cyan(){show_led_int(0,255,255);}
    void set_white(){show_led_int(255,255,255);}
    void set_none(){show_led_int(0,0,0);}
    pfunc cmd_func;
    void init_commands_with_args(){
      commandsTable["a"] = &show_led;
      //commandsTable["b"] = &blink_color;
      //commandsTable["c"] = &theaterChase;
      //commandsTable["d"] = &rainbow;
      //commandsTable["e"] = &theaterChaseRainbow;
      return;
    }

    void handle_command(std::string input, std::string delimiter = "/"){
      if (input.size() == 1){
        switch(input[0]){
          case 'R':
            CommandHandler::set_red();
            break;
          case 'B':
            CommandHandler::set_blue();
            break;
          case 'G':
            CommandHandler::set_green();
            break;
          case 'W':
            CommandHandler::set_white();
            break;
          case 'P':
            CommandHandler::set_purple();
            break;
          case 'C':
            CommandHandler::set_cyan();
            break;
          case 'Y':
            CommandHandler::set_yellow();
            break;
          case 'N':
            CommandHandler::set_none();
            break;
          }
        }
        else{
          std::vector<String> parses; // 10 maximum args
          size_t pos = 0; size_t i = 0;
          String token;
          //std::string tokens = s.substr(0, s.find(delimiter));
          while ((pos = input.find(delimiter)) != std::string::npos) {
              token = String(input.substr(0, pos).c_str());
              //std::cout << token << std::endl;
              parses.push_back(token);
              input.erase(0, pos + delimiter.length());
              i++;
          }
          //Parses is now an array of strings.
          cmd_func = commandsTable[parses[0]];
          parses.erase(parses.begin());
          CALL_MEMBER_FN(*this, this->cmd_func, parses);
          //cmd_func(parses); //This line fails no matter what I try to do. //Expected unqualified-id before '(' token
          //I want to call the function of this instance that is in commandsTable, with arguments defined in the vector parses.
          //The first element of the vector which is later erased is the function in commandsTable that is mapped
          //Other elements are arguments in the string.
        }
    }
    


    void blink(){
      delay(0.5*role_id);
      this->show_led_int(255, 255, 255);
      delay(0.5);
      this->show_led_int(0, 0, 0);
    }
    //void blink_color(int r, int b, int g){
    void blink_color(std::vector<String> & input){
      int r = String(input[0].c_str()).toInt();
      int b = String(input[1].c_str()).toInt();
      int g = String(input[2].c_str()).toInt();  
      uint32_t mycolor = strip.Color(r, b, g);
      delay(0.5*role_id);
      this->show_led_int(r, b, g);
      delay(0.5);
      this->show_led_int(0, 0, 0);
    }
    //void show_led(int r, int b, int g){
    void show_led(std::vector<String> & input){
      int r = String(input[0].c_str()).toInt();
      int b = String(input[1].c_str()).toInt();
      int g = String(input[2].c_str()).toInt();  
      uint32_t mycolor = strip.Color(r, b, g);
      strip.setPixelColor(0, mycolor);
      strip.setPixelColor(1, mycolor);
      strip.setPixelColor(2, mycolor);
      strip.setPixelColor(3, mycolor);
      strip.setPixelColor(4, mycolor);
      strip.setPixelColor(5, mycolor);
      strip.setPixelColor(6, mycolor);
      strip.setPixelColor(7, mycolor);
      strip.setPixelColor(8, mycolor);
      strip.setPixelColor(9, mycolor);
      strip.setPixelColor(10, mycolor);
      strip.setPixelColor(11, mycolor);
      strip.show();
    }
   void show_led_int(int r, int b, int g){
      uint32_t mycolor = strip.Color(r, b, g);
      strip.setPixelColor(0, mycolor);
      strip.setPixelColor(1, mycolor);
      strip.setPixelColor(2, mycolor);
      strip.setPixelColor(3, mycolor);
      strip.setPixelColor(4, mycolor);
      strip.setPixelColor(5, mycolor);
      strip.setPixelColor(6, mycolor);
      strip.setPixelColor(7, mycolor);
      strip.setPixelColor(8, mycolor);
      strip.setPixelColor(9, mycolor);
      strip.setPixelColor(10, mycolor);
      strip.setPixelColor(11, mycolor);
      strip.show();
    }
    //void colorWipe(uint32_t color, int wait) {
    void colorWipe(std::vector<String> & input){
      uint32_t color = String(input[0].c_str()).toInt();;
      int wait = String(input[0].c_str()).toInt();;
      for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
        strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
        delay(wait);                           //  Pause for a moment
      }
    }
    //void theaterChase(uint32_t color, int wait) {
    void theaterChase(std::vector<String> & input){
      uint32_t color = String(input[0].c_str()).toInt();
      int wait = String(input[1].c_str()).toInt();
      for(int a=0; a<10; a++) {  // Repeat 10 times...
      for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
        strip.clear();         //   Set all pixels in RAM to 0 (off)
        // 'c' counts up from 'b' to end of strip in steps of 3...
        for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        }
        strip.show(); // Update strip with new contents
        delay(wait);  // Pause for a moment
      }
      }
    }

    // Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
    //void rainbow(int wait) {
    void rainbow(std::vector<String> & input){
      int wait = String(input[0].c_str()).toInt();
      for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
      for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
        // Offset pixel hue by an amount to make one full revolution of the
        // color wheel (range of 65536) along the length of the strip
        // (strip.numPixels() steps):
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
        // optionally add saturation and value (brightness) (each 0 to 255).
        // Here we're using just the single-argument hue variant. The result
        // is passed through strip.gamma32() to provide 'truer' colors
        // before assigning to each pixel:
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
      }
    }

    // Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
    //void theaterChaseRainbow(int wait) {
    static void theaterChaseRainbow(std::vector<String> & input){
      int wait = String(input[0].c_str()).toInt();
      int firstPixelHue = 0;     // First pixel starts at red (hue 0)
      for(int a=0; a<30; a++) {  // Repeat 30 times...
      for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
        strip.clear();         //   Set all pixels in RAM to 0 (off)
        // 'c' counts up from 'b' to end of strip in increments of 3...
        for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        }
        strip.show();                // Update strip with new contents
        delay(wait);                 // Pause for a moment
        firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
      }
    }
  }
    void updateRole(std::vector<String> & input){
      this->role_id = input[0].toInt();
    }
    void updateLoc(std::vector<String> & input){
      this->x = input[0].toInt();
      this->y = input[1].toInt();
      EEPROM.write(X_ADDR, this->x);
      EEPROM.write(Y_ADDR, this->y);
    }
};

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
