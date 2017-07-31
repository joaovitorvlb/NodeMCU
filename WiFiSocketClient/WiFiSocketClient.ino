#include <ESP8266WiFi.h>

const char* ssid     = "ssid";
const char* password = "psk";

const char* host = "ip_server";
const int httpPort = 500;
// Use WiFiClient class to create TCP connections
WiFiClient client;


void setup() 
{
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("conectando no ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");  
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());

  delay(500);

  Serial.print("Conectando ao ");
  Serial.println(host);
  
  while (client.connect(host, httpPort) != 1) 
    {
      delay(500);
      Serial.print(":");
    }
  Serial.println("Conectado ao servidor");
  delay(500);
}



void loop() 
{
  if (client.available()) 
  {
    char c = client.read();
    Serial.print(c);
  }
  
  if (client.connected() == 0) 
  {
    while (client.connect(host, httpPort) == 0) 
    {
      delay(500);
      Serial.print(":");
    }
    Serial.println();
    Serial.println("Conectado ao servidor");
  }
}

