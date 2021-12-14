#define BLYNK_TEMPLATE_ID "TMPLwXgVwZdx"
#define BLYNK_DEVICE_NAME "Paan FYP"
#define BLYNK_AUTH_TOKEN "_rGJVF2vsGQZmRtohU3zJDZm04n39W_U"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>        
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Paanpap";
char pass[] = "keladigoreng";

int analogInPin  = A0;    // Analog input pin
int sensorValue; 
float calibration = 0.36; // Check Battery voltage using multimeter & add/subtract the value
float voltage;
int bat_percentage;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(115200);

  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  Blynk.begin(auth, ssid, pass);
}

void loop() {
	sensorValue = analogRead(analogInPin);
	voltage = (((sensorValue * 3.3) / 1024) * 2 + calibration); //multiply by two as voltage divider network is 100K & 100K Resistor

  	bat_percentage = mapfloat(voltage, 2.8, 4.2, 0, 100); //2.8V as Battery Cut off Voltage & 4.2V as Maximum Voltage
 
  	if (bat_percentage >= 100)
  	{
    	bat_percentage = 100;
  	}
  	if (bat_percentage <= 0)
  	{
    	bat_percentage = 1;
  	}
 
  Serial.print("Analog Value = ");
  Serial.print(sensorValue);
  Serial.print("\t Output Voltage = ");
  Serial.print(voltage);
  Serial.print("\t Battery Percentage = ");
  Serial.println(bat_percentage);
  delay(1000);

  Blynk.virtualWrite(V1, voltage);
  Blynk.virtualWrite(V2, bat_percentage);

  delay(500);

  //Blynk WiFi Status Update
  if (WiFi.status() != WL_CONNECTED)  
  {  
    Serial.println("WiFi Not Connected");  
  }

  else  
  {  
    Serial.println("WiFi Connected");    
  } 

    Blynk.run();
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}