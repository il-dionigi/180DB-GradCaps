#define MY_ROLE 0
#define CALL_MEMBER_FN(object,ptrToMember, args)  ((object).*(ptrToMember))(args)
#define X_ADDR 0
#define Y_ADDR 1
#define LED_PIN   4
#define LED_COUNT 12
#include <WiFi.h>
//#include <C:\Users\Showb\OneDrive\Documents\Arduino\libraries\arduino-esp32-master\libraries\WiFi\src\WiFi.h>
//#include <ArduinoSTL.h>
#include <map>
#include <vector>
#include <Adafruit_NeoPixel.h>
#include <iostream>
#include <string>
#include <EEPROM.h>
#include <stdio.h>
#include <sstream>
#include <NeoPixelBus.h>
//Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
NeoPixelBus <NeoGrbFeature, Neo800KbpsMethod> strip(LED_COUNT, LED_PIN);
//const uint32_t red = strip.Color(150,0,0);
//const uint32_t green = strip.Color(0,150,0);
//const uint32_t blue = strip.Color(0,0,150);
//const uint32_t yellow = strip.Color(200,130,0);
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}
#include <iostream>
class CommandHandler{
  public:
  typedef void (CommandHandler::*pfunc)(std::vector<String>&);
  CommandHandler(){
    x = EEPROM.read(X_ADDR);
    y = EEPROM.read(Y_ADDR);
    role_id = MY_ROLE;
    init_commands_with_args();
  }
  CommandHandler(int x, int y, int role_id){
    this->x = x;
    this->y = y;
    this->role_id = role_id;
    init_commands_with_args();
  }
    int x, y, role_id;
    std::map<String, pfunc> commandsTable; 
    void set_red(){show_led_int(150,0,0);}
    void set_green(){show_led_int(0,150,0);}
    void set_blue(){show_led_int(0,0,150);}
    void set_purple(){show_led_int(255, 0, 255);}
    void set_yellow(){show_led_int(255, 255, 0);}
    void set_cyan(){show_led_int(0,255,255);}
    void set_white(){show_led_int(255,255,255);}
    void set_none(){show_led_int(0,0,0);}
    //pfunc cmd_func;
    void init_commands_with_args(){
      commandsTable["ShowLED"] = &CommandHandler::show_led;
      commandsTable["BlinkColor"] = &CommandHandler::blink_color;
      commandsTable["TheaterChase"] = &CommandHandler::theaterChase;
      commandsTable["Rainbow"] = &CommandHandler::rainbow;
      commandsTable["TheaterChaseRainbow"] = &CommandHandler::theaterChaseRainbow;
      commandsTable["UpdateRole"] = &CommandHandler::updateRole;
      commandsTable["UpdateLoc"] = &CommandHandler::updateLoc;
      commandsTable["UpdateAllLoc"] = &CommandHandler::updateAllLoc;
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
              //Serial.print(String("TOKEN" + token));
              i++;
          }
          bool valid_cmd = commandsTable.count(parses[0]) > 0;
          //Parses is now an array of strings.
          if (valid_cmd){
            pfunc cmd_func = commandsTable[parses[0]];
            parses.erase(parses.begin());
            CALL_MEMBER_FN(*this, cmd_func, parses);
          }
          else{
            Serial.println(String("Invalid Command!" + parses[0])); 
          }
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
      //uint32_t mycolor = strip.Color(r, b, g);
      show_led_int(r,b,g);
      strip.Show();
    }
   void show_led_int(unsigned int r, unsigned int b, unsigned int g){
      RgbColor mycolor(r, b, g);
      strip.SetPixelColor(0, mycolor);
      strip.SetPixelColor(1, mycolor);
      strip.SetPixelColor(2, mycolor);
      strip.SetPixelColor(3, mycolor);
      strip.SetPixelColor(4, mycolor);
      strip.SetPixelColor(5, mycolor);
      strip.SetPixelColor(6, mycolor);
      strip.SetPixelColor(7, mycolor);
      strip.SetPixelColor(8, mycolor);
      strip.SetPixelColor(9, mycolor);
      strip.SetPixelColor(10, mycolor);
      strip.SetPixelColor(11, mycolor);
      strip.Show();
      Serial.print(String("My Color: " + String(r) + " " + String(b) + " " + String(g)));
    }
    void colorWipe(std::vector<String> & input){
      RgbColor color(String(input[0].c_str()).toInt(), String(input[1].c_str()).toInt(), String(input[2].c_str()).toInt());
      int wait = String(input[3].c_str()).toInt();;
      for(int i=0; i < LED_COUNT; i++) { // For each pixel in strip...
        strip.SetPixelColor(i, color);         //  Set pixel's color (in RAM)
        strip.Show();                          //  Update strip to match
        delay(wait);                           //  Pause for a moment
      }
    }
    void theaterChase(std::vector<String> & input){
      RgbColor color(String(input[0].c_str()).toInt(), String(input[1].c_str()).toInt(), String(input[2].c_str()).toInt());
      int wait = String(input[3].c_str()).toInt();
      Serial.println("vector_len:" + String(input.size()) + " " + String(wait));
      for(int a=0; a<10; a++) {  // Repeat 10 times...
      for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
        //strip.clear();         //   Set all pixels in RAM to 0 (off)
        // 'c' counts up from 'b' to end of strip in steps of 3...
        for(int c=b; c < LED_COUNT; c += 3) {
        strip.SetPixelColor(c, color); // Set pixel 'c' to value 'color'
        }
        strip.Show(); // Update strip with new contents
        delay(wait);  // Pause for a moment
      }
      }
    }
    void rainbow(std::vector<String> & input){
      int wait = String(input[0].c_str()).toInt();
      for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
      for(int i=0; i < LED_COUNT; i++) { // For each pixel in strip...
        // Offset pixel hue by an amount to make one full revolution of the
        // color wheel (range of 65536) along the length of the strip
        // (strip.numPixels() steps):
        float  hue   = (firstPixelHue + i * 65536L / LED_COUNT)/65536L;
        Serial.println(hue);
        // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
        // optionally add saturation and value (brightness) (each 0 to 255).
        // Here we're using just the single-argument hue variant. The result
        // is passed through strip.gamma32() to provide 'truer' colors
        // before assigning to each pixel:
        strip.SetPixelColor(i, HsbColor(hue, 1.0f, 1.0f));
      }
      strip.Show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
      }
    }
    void theaterChaseRainbow(std::vector<String> & input){
      int wait = String(input[0].c_str()).toInt();
      float firstPixelHue = 0.0f;     // First pixel starts at red (hue 0)
      for(int a=0; a<30; a++) {  // Repeat 30 times...
      for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
        //strip.Clear();         //   Set all pixels in RAM to 0 (off)
        // 'c' counts up from 'b' to end of strip in increments of 3...
        for(int c=b; c<LED_COUNT; c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        float  hue   = (firstPixelHue + c * 65536L / LED_COUNT)/65536L;
        Serial.println(hue);
        HsbColor color(hue, 1.0f, 1.0f); // hue -> RGB
        strip.SetPixelColor(c, color); // Set pixel 'c' to value 'color'
        }
        strip.Show();                // Update strip with new contents
        delay(wait);                 // Pause for a moment
        firstPixelHue += (1 / 90); // One cycle of color wheel over 90 frames
      }    
    }
  }
    void updateRole(std::vector<String> & input){
      this->role_id = input[0].toInt();
    }
    void updateLoc(std::vector<String> & input){
      if(input[0].toInt() == this->role_id){
        this->x = input[1].toInt();
        this->y = input[2].toInt();
        EEPROM.write(X_ADDR, this->x);
        EEPROM.write(Y_ADDR, this->y);
      }
    }
   void updateAllLoc(std::vector<String> & input){
      for(int i = input.size() - 1; i--; i >= 0){
        if(input[i-2].toInt() == this->role_id){
          this->x = input[i-1].toInt();
          this->y = input[i].toInt();
          EEPROM.write(X_ADDR, this->x);
          EEPROM.write(Y_ADDR, this->y);
          break;
        }
      }
    }
    void runBytes(std::vector<String> & input){
      void (*func) () = NULL;
      //func = mmap (0, sizeof(input[0]), PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);  
      //memcpy(func, input[0], sizeof(input[0]));
      //__builtin___clear_cache(func, func + sizeof(func));
      //return func();
    }
};
