#include <PubSubClient.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <iterator>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#define WLAN_SSID       "ece_private"
#define WLAN_PASS       "uclagradcap"
//#define AIO_SERVER      "192.168.0.114"
#define AIO_SERVERPORT  1883
#define AIO_SERVER      "192.168.0.10"
#define CHANNEL "test_channel"
#define PUB_CHANNEL "responses"
#define MSG_BUFFER_SIZE 50

//#define DEBUG 1
#define MY_ROLE 69

#define CALL_MEMBER_FN(object,ptrToMember, args)  ((object).*(ptrToMember))(args);
#define X_ADDR 0
#define Y_ADDR 1
#define OTA_FLAG 2
#define LED_PIN D4
#define LED_COUNT 12
