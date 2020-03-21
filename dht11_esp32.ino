#include <Adafruit_Sensor.h>  // add Adafruit_Sensor library
#include <DHT.h>        // add DHT library
#define DHTPIN 4        // define pin which is connected to DHT sensor
#define DHTTYPE DHT11   // define type of sensor, if you're another sensor change it

DHT dht(DHTPIN, DHTTYPE);
 
void setup()
{
Serial.begin(115200);
dht.begin();
}
 
void loop() {
// read humidity as percentage and temperature as celcius
float t = dht.readTemperature();
float h = dht.readHumidity();
 
// check if any reads failed
if (isnan(t) || isnan(h)) {
Serial.println("Failed to read from DHT sensor!");
return;
}
 
// print the result to serial monitor or terminal
Serial.print("Temperature: "); 
Serial.print(t);
Serial.print(" *C\t");
Serial.print("Humidity: ");
Serial.print(h);
Serial.println(" %");

delay(2000);
}
