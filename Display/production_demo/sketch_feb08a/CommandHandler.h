//#include <WiFi.h>
#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <EEPROM.h>
#include <stdio.h>
#include <sstream>
#include <Adafruit_NeoPixel.h>
#include <list>
#include <tuple>
#include "bitmap.h"
#include "automata.h"
#define MY_ROLE 14
#define CALL_MEMBER_FN(object,ptrToMember, args)  ((object).*(ptrToMember))(args);
#define X_ADDR 0
#define Y_ADDR 1
#define LED_PIN D4
#define LED_COUNT 12
#define NUM_ROWS 3
#define NUM_COLS 5
struct Colors{
unsigned int r,b,g;
};
class CommandHandler;
std::map<String, int> LocationArgIndex;
std::map<std::pair<int,int>, CommandHandler*> MyLEDBoards;
std::list<std::vector<String>> CommandsList;
std::list<Colors> FramesList;
class CommandHandler{
  public:
  typedef void (CommandHandler::*pfunc)(std::vector<String>&);
  CommandHandler() : strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800), _bitmap(NUM_ROWS, NUM_COLS, &strip, VERTICAL){
    //_bitmap = bitmap(NUM_ROWS, NUM_COLS, &strip);
    x = EEPROM.read(X_ADDR);
    y = EEPROM.read(Y_ADDR);
    role_id = MY_ROLE;
    init_commands_with_args();
  }
  CommandHandler(int x, int y, int role_id) : strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800), _bitmap(NUM_ROWS, NUM_COLS, &strip, VERTICAL){
    //_bitmap = bitmap(NUM_ROWS, NUM_COLS, &strip);
    this->x = x;
    this->y = y;
    this->role_id = role_id;
    init_commands_with_args();
  }
    int x, y, role_id;
    Adafruit_NeoPixel strip;
    bitmap _bitmap;
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
      //Add a command to iterate over frames.
      commandsTable["ShowAllLEDs"] = &CommandHandler::show_all_led; //Called as func/color(int,int,int) 
      commandsTable["ShowLED"] = &CommandHandler::show_led; //Called as func/x/y/color(int,int,int)/
      commandsTable["BlinkColor"] = &CommandHandler::blink_color; //Called as func/x/y/color/int/int
      commandsTable["TheaterChase"] = &CommandHandler::theaterChase; //Called as func/x/y/color(int/int/int)/int(wait)
      commandsTable["Rainbow"] = &CommandHandler::rainbow; //Called as func/x/y/int
      commandsTable["TheaterChaseRainbow"] = &CommandHandler::theaterChaseRainbow; //Called as func/x/y/int
      commandsTable["UpdateRole"] = &CommandHandler::updateRole; //Called as func/oldrole/newrole
      commandsTable["UpdateLoc"] = &CommandHandler::updateLoc; //Called as func/role/x/y
      commandsTable["UpdateAllLoc"] = &CommandHandler::updateAllLoc; //Dont use;
      commandsTable["BitmapGenMsgV"] = &CommandHandler::bm_genmsg_v; //Called as func/x/y/string
      commandsTable["BitmapGenMsgH"] = &CommandHandler::bm_genmsg_h; //Called as func/x/y/string
      commandsTable["BitmapGenSeq"] = &CommandHandler::bm_gen_seq; //called as func/x/y/string
      commandsTable["BitmapShowSeq"] = &CommandHandler::bm_show_seq; //called as func/x/y/string
      commandsTable["StoreFrame"] = &CommandHandler::store_frame;
      commandsTable["StartFrames"] = &CommandHandler::show_frames;
      commandsTable["Auto"] = &CommandHandler::call_automata;
      return;
    }
    void call_automata(std::vector<String> & input){
      int r = input[0].toInt();
      int b = input[1].toInt();
      int g = input[2].toInt();
      automata(&strip, strip.Color(r, b, g), this->x, this->y,
      input[3].c_str()[0]);
    }
    void store_frame(std::vector<String> & input){
      //This vector should be somewhat huge, in the following structure:
      //String 0: Show_LED/x/y/c0/c1/c2
      bool myFrame = check_vector_loc(input);
      if(myFrame){
        Colors colorObj;
        colorObj.r = String(input[2]).toInt();
        colorObj.b = String(input[3]).toInt();
        colorObj.g = String(input[4]).toInt();
        FramesList.push_back(colorObj);
        //CommandsList.push_back(input);
      }
    }
    void show_frames(std::vector<String> & input){
      for (std::list<Colors>::iterator it = FramesList.begin() ; it != FramesList.end(); ++it){
        unsigned int r, g, b;
        r = it->r;
        g = it->g;
        b = it->b;
        show_led_int(r,g,b);
        delay(.016);
      }
    }
    void bm_genmsg_v(std::vector<String> & input){
      _bitmap.set_orientation(VERTICAL);
      bm_genmsg(input);  
    }
    void bm_genmsg_h(std::vector<String> & input){
      _bitmap.set_orientation(HORIZONTAL);
      bm_genmsg(input);  
    }
    void bm_genmsg(std::vector<String> & input){
      _bitmap.generate_msg_v((char*)input[0].c_str());
      Serial.println("Generated Message Successfully!");  
    }
    void bm_gen_seq(std::vector<String> & input){
      _bitmap.generate_sequence_v(String(input[0].c_str()).toInt(), x, y);
    }
    void bm_show_seq(std::vector<String> & input){
      //Color 
      int r = String(input[1].c_str()).toInt();
      int b = String(input[2].c_str()).toInt();
      int g = String(input[3].c_str()).toInt();
      //uint32_t color = 0; 
      uint32_t color = strip.Color(r, b, g);
      long wait_time = atol(input[0].c_str());
      Serial.println("Expected wait time for show_sequence:");
      Serial.println(wait_time);
      _bitmap.show_sequence_delay(wait_time, color);
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
          std::vector<String> parses; 
          size_t pos = 0; size_t i = 0;
          String token;
          while ((pos = input.find(delimiter)) != std::string::npos) {
              token = String(input.substr(0, pos).c_str());
              //std::cout << token << std::endl;
              parses.push_back(token);
              input.erase(0, pos + delimiter.length());
              Serial.print(String("TOKEN" + token + "\n"));
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
            Serial.println(String("Invalid Command!" + parses[0] + "\n")); 
          }
        }
    }
    inline bool check_vector_role(std::vector<String> & input, int role_index = 0){
      return String(input[role_index].c_str()).toInt() == this->role_id; 
    }
    inline bool check_vector_loc(std::vector<String> & input, int x_index = 0, int y_index = 1){
      return (String(input[x_index].c_str()).toInt() == this->x) && (String(input[y_index].c_str()).toInt() == this->y); 
    }
    void blink(){
      this->show_led_int(255, 255, 255);
      delay(0.5);
      this->show_led_int(0, 0, 0);
    }
    void blink_color(std::vector<String> & input){
      int r = String(input[0].c_str()).toInt();
      int b = String(input[1].c_str()).toInt();
      int g = String(input[2].c_str()).toInt();  
      this->show_led_int(r, b, g);
      delay(0.5);
      this->show_led_int(0, 0, 0);
    }
    void blink_color(int r, int b, int g, int wait = 0.5){
      this->show_led_int(r, b, g);
      delay(wait);
      this->show_led_int(0, 0, 0);
    }
    void show_led(std::vector<String> & input){
       if (check_vector_loc(input)){
          int r = String(input[0].c_str()).toInt();
          int b = String(input[1].c_str()).toInt();
          int g = String(input[2].c_str()).toInt();  
          show_led_int(r,b,g);
      }
    }
    void show_all_led(std::vector<String> & input){
      int r = String(input[0].c_str()).toInt();
      int b = String(input[1].c_str()).toInt();
      int g = String(input[2].c_str()).toInt();  
      show_led_int(r,b,g);
    }
   void show_led_int(unsigned int r, unsigned int b, unsigned int g){
      uint32_t mycolor = strip.Color(r, b, g);
      #ifdef ESP32
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
      #elif defined(ESP8266)
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
      Serial.print(String("My Color: " + String(r) + " " + String(b) + " " + String(g)));
      #endif
    }
    void corners(){
      uint32_t red = strip.Color(150,0,0);
      uint32_t green = strip.Color(0,150,0);
      uint32_t blue = strip.Color(0,0,150);
      uint32_t yellow = strip.Color(200,130,0);
      strip.setPixelColor(11, green);
      strip.setPixelColor(0, green);
      strip.setPixelColor(1, green);

      strip.setPixelColor(2, blue);
      strip.setPixelColor(3, blue);
      strip.setPixelColor(4, blue);

      strip.setPixelColor(5, red);
      strip.setPixelColor(6, red);
      strip.setPixelColor(7, red);

      strip.setPixelColor(8, yellow);
      strip.setPixelColor(9, yellow);
      strip.setPixelColor(10, yellow);
      strip.show();
    }

  // Some functions of our own for creating animated effects -----------------

  // Fill strip pixels one after another with a color. Strip is NOT cleared
  // first; anything there will be covered pixel by pixel. Pass in color
  // (as a single 'packed' 32-bit value, which you can get by calling
  // strip.Color(red, green, blue) as shown in the loop() function above),
  // and a delay time (in milliseconds) between pixels.
  void colorWipe(std::vector<String> & input) {
    if(check_vector_loc(input)){
      int r = String(input[2].c_str()).toInt();
      int b = String(input[3].c_str()).toInt();
      int g = String(input[4].c_str()).toInt();  
      uint32_t color = strip.Color(r,b,g);
      int wait = String(input[5].c_str()).toInt();
      for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
        strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
        delay(wait);                           //  Pause for a moment
      }
    }
  }

  // Theater-marquee-style chasing lights. Pass in a color (32-bit value,
  // a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
  // between frames.
  void theaterChase(std::vector<String> & input) {
    if(check_vector_loc(input)){
      int r = String(input[2].c_str()).toInt();
      int b = String(input[3].c_str()).toInt();
      int g = String(input[4].c_str()).toInt();  
      uint32_t color = strip.Color(r,b,g);
      int wait = String(input[5].c_str()).toInt();
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
  }

  // Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
  void rainbow(std::vector<String> & input) {
    if(check_vector_loc(input)){
      int wait = String(input[3].c_str()).toInt();
      // Hue of first pixel runs 5 complete loops through the color wheel.
      // Color wheel has a range of 65536 but it's OK if we roll over, so
      // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
      // means we'll make 5*65536/256 = 1280 passes through this outer loop:
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
  }

  // Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
  void theaterChaseRainbow(std::vector<String> & input) {
    if(check_vector_loc(input)){
      int wait = String(input[2].c_str()).toInt();
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
    String get_status(){
      std::stringstream fmt;
      fmt << "Role: " << role_id << "x: " << x << "y: " << y << "r,g,b: " << strip.getPixelColor(2);
      return String(fmt.str().c_str());
    }
    String get_error(const char* error, const char* values){
      std::stringstream fmt;
      fmt << "Role: " << role_id << "x: " << x << "y: " << y << "r,g,b: " << error << values;
      return String(fmt.str().c_str());
    }
};

void init_location_arg_index(){
  LocationArgIndex["ShowAllLEDs"] = -1; //Called as func/color(int,int,int)
  LocationArgIndex["ShowLED"] = 1; //Called as func/x/y/color(int,int,int)/
  LocationArgIndex["BlinkColor"] = 1; //Called as func/x/y/color/int/int
  LocationArgIndex["TheaterChase"] = 1; //Called as func/x/y/color(int/int/int)/int(wait)
  LocationArgIndex["Rainbow"] = 1; //Called as func/x/y/int
  LocationArgIndex["TheaterChaseRainbow"] = 1; //Called as func/x/y/int
  LocationArgIndex["UpdateRole"] = -1; //Called as func/oldrole/newrole
  LocationArgIndex["UpdateLoc"] = 2; //Called as func/role/x/y
  LocationArgIndex["UpdateAllLoc"] = -1; //Dont use;
  LocationArgIndex["BitmapGenMsg"] = 1; //Called as func/x/y/string
  LocationArgIndex["BitmapGenSeq"] = 1; //called as func/x/y/string
  LocationArgIndex["BitmapShowSeq"] = 1; //called as func/x/y/string
  //LocationArgIndex["Auto"] = &(automata);
}
//Currently only one support for one led board
