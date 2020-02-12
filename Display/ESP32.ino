#include <PubSubClient.h>
#include <stdio.h>
#include "CommandHandler.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
//#define WLAN_SSID       "ece_private"
//#define WLAN_PASS       "uclagradcap"
#define WLAN_SSID       "ASUS_50_2G"
#define WLAN_PASS       "1337h4v3fun#97"
#define AIO_SERVER      "192.168.50.17"
#define AIO_SERVERPORT  1883
#define CHANNEL "test_channel"
using namespace std;
WiFiClient client;
PubSubClient mqtt(client);
CommandHandler myCommandHandler;
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
    try{
    
    myCommandHandler.handle_command(std::string(messageTemp.c_str()));
    }
    catch (const std::exception &exc){
      ESP_LOGE(APP_TAG, "Exception: %s", exc.what() );
    }
  }
}
//Adafruit_MQTT_Subscribe test = Adafruit_MQTT_Subscribe(&mqtt, "test_channel");
void setup() {
  //myCommandHandler.show_led_int(0,0,0);
  Serial.begin(115200);
  strip.Begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.Show();            // Turn OFF all pixels ASAP
  //strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  //delay(1000);

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
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
        myCommandHandler.show_led_int(255, 0, 0);
        delay(2000);
        myCommandHandler.show_led_int(0, 0, 0);
        delay(3000);
      }
    }
  }
void loop() {
  //portDISABLE_INTERRUPTS();
  if (!client.connected()) {
    reconnect();
  }
  mqtt.loop();
  //portENABLE_INTERRUPTS();
  delay(1000);
  //Any other publish logic should go here.
}
