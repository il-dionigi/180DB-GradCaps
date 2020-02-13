#include <PubSubClient.h>
#include <stdio.h>
#include "CommandHandler.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <sstream>
#include <vector>
#include <iterator>
//#define WLAN_SSID       "ece_private"
//#define WLAN_PASS       "uclagradcap"
#define WLAN_SSID       "ASUS_50_2G"
#define WLAN_PASS       "1337h4v3fun#97"
#define AIO_SERVER      "192.168.50.17"
#define AIO_SERVERPORT  1883
#define CHANNEL "test_channel"
//using namespace std;
WiFiClient client;
PubSubClient mqtt(client);
CommandHandler myCommandHandler;

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
void callback(char* topic, uint8_t* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp; 
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  if (std::string(topic) == CHANNEL){
    //try{
      //Separate by newlines
      std::string arg1 = std::string(messageTemp.c_str());
      std::string arg2 = std::string(String("\n").c_str());
      std::vector<String> cmds_list = my_split(arg1, arg2);
      for(size_t i = 0; i < cmds_list.size(); i++){
        std::string arg1 = std::string(cmds_list[i].c_str());
        std::string arg2 = std::string(String("/").c_str());
        std::vector<String> this_cmd_vector = my_split(arg1, arg2);
        //cmd_handle = MyLedBoards[this_cmd_vector[1].toInt(), this_cmd_vector[2].c_str().toInt()]
        bool valid_cmd = myCommandHandler.commandsTable.count(this_cmd_vector[0]) > 0;
        if (valid_cmd){
          int location_arg_index = LocationArgIndex[this_cmd_vector[0]];
          //CommandHandler* cmd_handle = MyLedBoards[{this_cmd_vector[location_arg_index].toInt(), this_cmd_vector[location_arg_index+1].c_str().toInt()}];
          myCommandHandler.handle_command(std::string(messageTemp.c_str()));
          //
        //}
      }
    }
    //catch (const std::exception &exc){
    //  ESP_LOGE(APP_TAG, "Exception: %s", exc.what() );
    //}
  }
}
//Adafruit_MQTT_Subscribe test = Adafruit_MQTT_Subscribe(&mqtt, "test_channel");
void setup() {
  //myCommandHandler.show_led_int(0,0,0);
  //MyLEDBoards[{x, y}] = &myCommandHandler();
  init_location_arg_index();
  std::map<std::pair<int, int>, CommandHandler*>::iterator it = MyLEDBoards.begin();
  for (std::pair<std::pair<int,int>, CommandHandler*> element : MyLEDBoards) {
    std::pair<int,int> loc = element.first;
    CommandHandler* cmd_handle = element.second;
    #ifdef ESP32
    cmd_handle->strip.Begin();
    cmd_handle->strip.show();
    #elif defined(ESP8266)
    cmd_handle->strip.begin();
    cmd_handle->strip.show();
    #endif
  }
  // Iterate over the map using Iterator till end.
  Serial.begin(115200);

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    WiFi.begin(WLAN_SSID, WLAN_PASS);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.setServer(AIO_SERVER, AIO_SERVERPORT);
  mqtt.setCallback(callback);
  mqtt.subscribe(CHANNEL);
}


void reconnect(){
  while (!mqtt.connected()) {
      Serial.print("Attempting MQTT connection...");
      // Attempt to connect
      if (mqtt.connect(String("ESP32 Role: " + String(myCommandHandler.role_id)).c_str())) {
        Serial.println("connected");
        // Subscribe
        mqtt.subscribe(CHANNEL);
      } else {
        Serial.print("failed, rc=");
        Serial.print(mqtt.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        //myCommandHandler.show_led_int(255, 0, 0);

        //Blink red for two seconds, then shut off
        for (std::pair<std::pair<int,int>, CommandHandler*> element : MyLEDBoards) {
          std::pair<int,int> loc = element.first;
          CommandHandler* cmd_handle = element.second;
          cmd_handle -> show_led_int(255, 0, 0);
        }
        delay(2000);
        for (std::pair<std::pair<int,int>, CommandHandler*> element : MyLEDBoards) {
            std::pair<int,int> loc = element.first;
            CommandHandler* cmd_handle = element.second;
            cmd_handle -> show_led_int(0, 0, 0);
          }
        delay(3000);
      }
    }
  }

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  mqtt.loop();
  delay(1000);
  //Any other publish logic should go here.
}
