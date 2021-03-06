#include "CommandHandler.h"
#include "includes.h"
using namespace std;
WiFiClient client;
PubSubClient mqtt(client);
CommandHandler myCommandHandler;
char msg[MSG_BUFFER_SIZE];
void callback(char* topic, uint8_t* message, unsigned int length) {
    int i = 0;
    for(; i < length; i++){
      msg[i] = message[i];  
    }
    msg[i] = '\0';
    #if defined(DEBUG)
    Serial.println(msg);
    Serial.println(String("topic") + String(topic));
    #endif
    String messageTemp(msg);
    if (strcmp(topic, messageTemp.c_str())){
      std::vector<String> messageVec = my_split(messageTemp.c_str());
      for (std::vector<String>::iterator it = messageVec.begin() ; it != messageVec.end(); ++it){
        //bool valid_cmd = myCommandHandler.commandsTable.count(*it) > 0;
        std::string cmd_name = std::string(it->c_str());
        //Serial.println(cmd_name.c_str());
        cmd_name = cmd_name.substr(0, cmd_name.find("/"));
        #if defined(DEBUG)
          Serial.println(cmd_name.c_str());
        #endif
        bool valid_cmd = myCommandHandler.commandsTable.count(String(cmd_name.c_str())) > 0;
        //Serial.println(valid_cmd);
        if (valid_cmd || it->length() == 1)  {
          #if defined(DEBUG)
          Serial.println("Handling command ...");
          #endif
          myCommandHandler.handle_command(std::string(it->c_str()));
        }
        else{
          myCommandHandler.blink();
          #if defined(DEBUG)
          Serial.print("Got an invalid command \n");
          Serial.println((*it).c_str());
          #endif
          String error = myCommandHandler.get_error("Invalid Command: ", it->c_str());
          //mqtt.publish(PUB_CHANNEL, error.c_str());
        }
      }
      //mqtt.publish(PUB_CHANNEL, myCommandHandler.get_status().c_str());
     }
}
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(LED_PIN, OUTPUT);  
  Serial.begin(115200);
  delay(10);
  myCommandHandler.strip.begin();
  myCommandHandler.show_led_int(255, 0, 0);
  myCommandHandler.strip.show();
  delay(10);
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    myCommandHandler.blink_color(100, 15, 0, 200);
    Serial.print(".");
  }
  Serial.println();
  //--OTA--
  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname(String(MY_ROLE).c_str());//String(MY_ROLE));  
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
  //mqtt.subscribe(&test);
  //MQTT_connect();
  mqtt.setServer(AIO_SERVER, AIO_SERVERPORT);
  mqtt.setCallback(callback);
  mqtt.subscribe(CHANNEL); 
}

uint32_t x = 0;

uint32_t timer = millis();

void loop() {
  if(flag_ota_program){
    myCommandHandler.set_cyan();
    ArduinoOTA.handle();
  }
  else{
    mqtt.loop();
    if(timer - millis() > 1000*60){
      timer = millis();
      if (! mqtt.connected()) {
        reconnect(); //Is this why they keep disconnecting?  
      }
    }
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void reconnect() {
  // Loop until we're reconnected
  while (!mqtt.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(MY_ROLE, HEX);
    // Attempt to connect
    if (mqtt.connect(clientId.c_str())) {
      #if defined(DEBUG)
      Serial.println("connected");
      #endif
      // Once connected, publish an announcement...
      //mqtt.publish(PUB_CHANNEL, "hello world");
      // ... and resubscribe
      mqtt.setServer(AIO_SERVER, AIO_SERVERPORT);
      mqtt.setCallback(callback);
      mqtt.subscribe(CHANNEL); 
      myCommandHandler.blink_color(0, 255, 0, 1000);
    } else {
      #if defined(DEBUG)
      Serial.print("failed, rc=");
      Serial.print(mqtt.state());
      Serial.println(" try again in 5 seconds");
      #endif
      //mqtt.publish(CHANNEL, "hello world_fail");
      myCommandHandler.blink_color(255, 0, 0, 1000); //Does internal delays
    }
  }
}
