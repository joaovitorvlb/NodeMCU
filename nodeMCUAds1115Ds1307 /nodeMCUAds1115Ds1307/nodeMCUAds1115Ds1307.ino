#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include "RTClib.h"

int val = 0;

#define VOLTAGE_MAX      24.0
#define CURRENT_MAX      1200.0
#define ADC_MAXCOUNTS    17130.0

#define LD1   12

#define RL1   15
#define RL2   13

#define S1    0
#define S2    2
#define S3    14

int ano = 0;
int mes = 0;
int dia = 0;
int horr = 0;
int minn = 0;
int segg = 0;
int flag = 0;

float acumvcc = 0;
float acumicc = 0;
float vresult = 0;
float iresult = 0;

RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"domingo", "segunda", "terça", "quarta", "quinta", "sexta", "sábado"};

Adafruit_ADS1115 ads;

void setup(void) 
{
  pinMode(RL1, OUTPUT);      // sets the digital pin 13 as output
  pinMode(S1, INPUT);
  
  Serial.begin(9600);

  ads.begin();
  
  if (! rtc.begin()) 
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }
}

void loop(void) 
{
 

//----------Rotina do rtc------------------------------
  DateTime now = rtc.now();
  
  
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);

  horr = (now.hour());
  minn = (now.minute());
  segg = (now.second());
  
  Serial.print(") ");
  Serial.print(horr);
  Serial.print(':');
  Serial.print(minn);
  Serial.print(':');
  Serial.print(segg);
  Serial.println();
  
  //Serial.println();
  delay(500);

  int16_t adc0, adc1, adc2, adc3;

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  float voltage = adc0 * (VOLTAGE_MAX / ADC_MAXCOUNTS);
  float current = adc1 * (CURRENT_MAX / ADC_MAXCOUNTS);

  Serial.print("vcc: "); Serial.print(voltage);
  Serial.print("  icc: "); Serial.println(current);
  Serial.println(" ");

  val = digitalRead(S1);   // read the input pin
  digitalWrite(RL1, val);  
}





