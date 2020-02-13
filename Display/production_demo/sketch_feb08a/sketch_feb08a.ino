//#include <PubSubClient.h>
#include <stdio.h>
#include "CommandHandler.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <sstream>
#include <vector>
#include <iterator>
#define WLAN_SSID       "ece_private"
#define WLAN_PASS       "uclagradcap"
//#define WLAN_SSID       "ASUS_50_2G"
//#define WLAN_PASS       "1337h4v3fun#97"
//#define AIO_SERVER      "192.168.50.17"
#define AIO_SERVER "192.168.0.100"
#define AIO_SERVERPORT  1883
#define CHANNEL "test_channel"
#include <ESP8266WiFi.h>
//using namespace std;
WiFiClient client;
CommandHandler myCommandHandler;
// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT);

/****************************** Feeds ***************************************/

// Setup a feed called 'test' for subscribing to changes.
Adafruit_MQTT_Subscribe test = Adafruit_MQTT_Subscribe(&mqtt, "test_channel");

/*************************** Sketch Code ************************************/

std::vector<String> my_split(std::string &input, std::string & delimiter) {
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
    return parses;
}

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  Serial.begin(115200);
  delay(10);
  myCommandHandler.strip.begin();
  myCommandHandler.strip.show();
  myCommandHandler.strip.setBrightness(255);
  delay(10);
  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&test);
}

uint32_t x = 0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
  if (subscription == &test){
    String messageTemp = String((char *)test.lastread);
    Serial.print(messageTemp);
    myCommandHandler.handle_command(std::string(messageTemp.c_str()));
      /*
      std::string arg1 = std::string(messageTemp.c_str());
      std::string arg2 = std::string(String("\n").c_str());
      std::vector<String> cmds_list = my_split(arg1, arg2);
      for(size_t i = 0; i < cmds_list.size(); i++){
        std::string arg1 = std::string(cmds_list[i].c_str());
        std::string arg2 = std::string(String("/").c_str());
        std::vector<String> this_cmd_vector = my_split(arg1, arg2);
        //cmd_handle = MyLedBoards[this_cmd_vector[1].toInt(), this_cmd_vector[2].c_str().toInt()]
        bool valid_cmd = myCommandHandler.commandsTable.count(this_cmd_vector[0]) > 0;
        Serial.print(this_cmd_vector[0]);
        Serial.print(valid_cmd);
        if (valid_cmd){
          int location_arg_index = LocationArgIndex[this_cmd_vector[0]];
          //CommandHandler* cmd_handle = MyLedBoards[{this_cmd_vector[location_arg_index].toInt(), this_cmd_vector[location_arg_index+1].c_str().toInt()}];
          myCommandHandler.handle_command(std::string(cmds_list[i].c_str()));
         }
        }
        */
      
    }
  }
  if (! mqtt.ping()) {
    mqtt.disconnect();
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}

void colorWipe(uint32_t color) {
  for (int i = 0; i < myCommandHandler.strip.numPixels(); i++) { // For each pixel in strip...
    myCommandHandler.strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    myCommandHandler.strip.show();                          //  Update strip to match
  }
}
