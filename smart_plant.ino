/*
  APDS9960 - All sensor data from APDS9960

  This example reads all data from the on-board APDS9960 sensor of the
  Nano 33 BLE Sense:
   - color RGB (red, green, blue)
   - proximity
   - gesture
  and prints updates to the Serial Monitor every 100 ms.

  The circuit:
  - Arduino Nano 33 BLE Sense

  This example code is in the public domain.
*/

#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;


void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for serial monitor to open

  carrier.noCase();
  if (!carrier.begin()) {
    Serial.println("Error");
    while (true); // Stop forever
  }
}

float humidity;
float temperature;
int light;
int moisture;

int moistPin;

unsigned long lastUpdate = 0;

void loop() {
 //read temperature and humidity
  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();
 
  //read raw moisture value
  int raw_moisture = analogRead(moistPin);
 
  //map raw moisture to a scale of 0 - 100
  moisture = map(raw_moisture, 0, 1023, 100, 0);

// Read Light
  while(!carrier.Light.colorAvailable()) {
    delay(5);
  }
  
  int none;
  carrier.Light.readColor(none, none, none, light);

  // Serial.println(millis() - lastUpdate);

  // Print updates every 100ms
  if (millis() - lastUpdate > 60000) {
    lastUpdate = millis();
    Serial.print("LIGHT TURNED ON||");
    Serial.println(light);
    Serial.print("TEMP||");
    Serial.println(temperature);
    Serial.print("HUMIDITY||");
    Serial.println(humidity);
    Serial.print("MOISTURE||");
    Serial.println(moisture);
  }




}
