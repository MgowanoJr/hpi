
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;
int moistPin;
float humidity;
float temperature;
int light;
int moisture;

void setup() {
  Serial.begin(9600);
    // This delay gives the chance to wait for a Serial Monitor without blocking if none is found

  while (!Serial); // Wait for serial monitor to open

  carrier.noCase();
  if (!carrier.begin()) {
    Serial.println("Error");
    while (true); // Stop forever
  } 
}


unsigned long lastUpdate = 0;

void loop() {
 //read temperature and humidity
  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();
 
  //read raw moisture value
  int raw_moisture = analogRead(A5);
 
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
  if (millis() - lastUpdate > 600) {
    lastUpdate = millis();
    Serial.print("LIGHT||");
    Serial.println(light,1);
    Serial.print("TEMP||");
    Serial.println(temperature,1);
    Serial.print("HUMIDITY||");
    Serial.println(humidity,1);
    Serial.print("MOISTURE||");
    Serial.println(moisture,1);
  }




}
