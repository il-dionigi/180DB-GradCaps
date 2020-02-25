The//#include <PubSubClient.h>
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
#define RESP_CHANNEL "client_response"
#include <ESP8266WiFi.h>

//OTA Dependencies
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

//using namespace std;
WiFiClient client;
CommandHandler myCommandHandler;
// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT);
/****************************** Feeds ***************************************/

// Setup a feed called 'test' for subscribing to changes.
Adafruit_MQTT_Subscribe test = Adafruit_MQTT_Subscribe(&mqtt, CHANNEL);
Adafruit_MQTT_Publish test_pub = Adafruit_MQTT_Publish(&mqtt, RESP_CHANNEL);

std::vector<String> my_split(const char * sentence)
{
  std::stringstream ss(sentence);
  std::string to;
  std::vector<String> output;
  if (sentence != NULL)
  {
    while(std::getline(ss,to,'\n')){
      output.push_back(String(to.c_str()));
    }
  }

  return output;
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
  /*
  myCommandHandler.x = 0;
  myCommandHandler.y = 0;
  myCommandHandler._bitmap.generate_msg_v("UCLA");
  myCommandHandler._bitmap.generate_sequence_v(5, 0, 0);
  myCommandHandler._bitmap.generate_sequence_v(5, 0, 1);
  myCommandHandler._bitmap.generate_sequence_v(5, 0, 2);
  myCommandHandler._bitmap.generate_sequence_v(5, 0, 3);
  myCommandHandler._bitmap.generate_sequence_v(5, 0, 4);
  */
  //bitmap.show_sequence
  delay(10);
  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  //--OTA--

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("100");//String(MY_ROLE));  

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();

  //---

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&test);
}

uint32_t x = 0;

void loop() {
  if(flag_ota_program){
    ArduinoOTA.handle();
  }
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
    std::vector<String> messageVec = my_split(messageTemp.c_str());
    for (std::vector<String>::iterator it = messageVec.begin() ; it != messageVec.end(); ++it){
      //bool valid_cmd = myCommandHandler.commandsTable.count(*it) > 0;
      std::string cmd_name = std::string(it->c_str());
      //Serial.println(cmd_name.c_str());
      cmd_name = cmd_name.substr(0, cmd_name.find("/"));
      Serial.println(cmd_name.c_str());
      bool valid_cmd = myCommandHandler.commandsTable.count(String(cmd_name.c_str())) > 0;
      //Serial.println(valid_cmd);
      if (valid_cmd || it->length() == 1)  {
        Serial.println("Handling command ...");
        myCommandHandler.handle_command(std::string(it->c_str()));
      }
      else{
        myCommandHandler.blink();
        Serial.print("Got an invalid command \n");
        Serial.print((*it).c_str());
        String error = myCommandHandler.get_error("Invalid Command: ", it->c_str());
        //test_pub.publish(error.c_str());
      }
    }
    //test_pub.publish(myCommandHandler.get_status().c_str());
   }
  }
  if (! mqtt.ping()) {
    mqtt.disconnect(); //Is this why they keep disconnecting?
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
