#include "arduino_secrets.h"
#include "thingProperties.h"

unsigned long previousMillis;
unsigned long sampleRate = 1000;

void setup() 
{
  Serial.begin(115200);
  delay(1000);

  // fix for LOLIN C3 mini V1.0 tx power bug
  WiFi.begin();
  WiFi.setTxPower(WIFI_POWER_8_5dBm);


  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(4);
  ArduinoCloud.printDebugInfo();

  pinMode(10, OUTPUT);
  previousMillis = millis();
}

void loop() 
{
  ArduinoCloud.update();

  if ((unsigned long)(millis() - previousMillis > sampleRate))
  {
    moisture = analogRead(A0);
    previousMillis = millis();
  }
  
  if (moisture < thresholdLow) pump = false;
  else if (moisture > thresholdHigh) pump = true;
  digitalWrite(10, pump);
}

void onThresholdLowChange() {
  // Do something
}

void onThresholdHighChange() {
  // Do something
}
