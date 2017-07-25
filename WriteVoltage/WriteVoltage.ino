#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
char ssid[] = "Joao Vitor";          //  your network SSID (name) 
char pass[] = "mj110032";            // your network password
int status = WL_IDLE_STATUS;
WiFiClient  client;
// On ESP8266:  0 - 1023 maps to 0 - 1 volts
#define VOLTAGE_MAX 24.0
#define VOLTAGE_MAXCOUNTS 1023.0

unsigned long myChannelNumber = 222669;
const char * myWriteAPIKey = "91ZKV99AA1UVMKAE";

void setup()
{ 
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  ThingSpeak.begin(client);
}

void loop() 
{
  int sensorValue = analogRead(A0);
  
  float voltage = sensorValue * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  ThingSpeak.writeField(myChannelNumber, 3, voltage, myWriteAPIKey);
  Serial.println(voltage);
  delay(10000); // ThingSpeak will only accept updates every 15 seconds.
}
