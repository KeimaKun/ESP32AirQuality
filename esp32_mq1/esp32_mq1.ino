#include "AWSKey.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "Wifi.h"

const char WIFI_SSID[] = "PUT_WIFI_SSID";                             //change this
const char WIFI_PASS[] = "PUT_WIFI_PASSWORD";                         //change this
const char AWS_ENDPOINT[] = "xxxxxxx.iot.REGION.amazonaws.com";       //change this

#define AWS_CLIENT_ID        "mq2_1_ClientId"                          //change this
#define AWS_PUBLISH          "mq2_1/uplink"                           //change this
#define AWS_SUBSCRIBE        "mq2_1/downlink"                         //change this

#define AO_PIN 34  // ESP32's pin GPIO36 connected to AO pin of the MQ2 sensor

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

unsigned long last1;

void setup() {
  // initialize serial communication
  Serial.begin(115200);
  AWS_CONNECT();
  Serial.println("Warming up the MQ2 sensor");
  delay(20000);  // wait for the MQ2 to warm up
}

void loop() {
  if (millis() - last1 >= 10000) {
    last1 = millis();
    uplink();
  }

  client.loop();
  delay(1000);
}

/*-----------------------------------------------------------------------*/
void AWS_CONNECT() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.println("Wi-Fi Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  client.setServer(AWS_ENDPOINT, 8883);
  client.setCallback(downlink);

  while (!client.connect(AWS_CLIENT_ID)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  if (!client.connected()) {
    Serial.println("AWS-IoT-Core Timeout!");
    return;
  }

  client.subscribe(AWS_SUBSCRIBE);
  Serial.println("AWS-IoT-Cotre Connected.");
}

/*-----------------------------------------------------------------------*/
void uplink()
{
  int gasValue = analogRead(AO_PIN);

  StaticJsonDocument<200> sensor_data;
  sensor_data["nid"] = AWS_CLIENT_ID;
  sensor_data["mq2_1"] = gasValue;
  
  char json[512];
  serializeJson(sensor_data, json); // print to client
  client.publish(AWS_PUBLISH, json);
  Serial.println(json);
}

/*-----------------------------------------------------------------------*/
void downlink(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);

  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);
}
