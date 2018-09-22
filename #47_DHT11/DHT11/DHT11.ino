#include "DHT.h"
#define DHTPIN A0 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  dht.begin();
}
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // Read temperature as Celsius (the default)
  float hic = dht.computeHeatIndex(t, h, false);
  // Compute heat index in Celsius (isFahreheit = false)

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("*C\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.println(" *C ");
  
  delay(2000);

}
