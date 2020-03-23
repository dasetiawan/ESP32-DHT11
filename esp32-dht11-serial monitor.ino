#include <Adafruit_Sensor.h>
#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float t; // variable for temperature
float h; // variable for humidity

void setup()
{
Serial.begin(115200);
dht.begin();
}
 
void loop() {
 readData();
 // print the result to Terminal
 Serial.print("Temperature: ");
 Serial.print(t);
 Serial.print(" *C\t");
 Serial.print("Humidity: ");
 Serial.print(h);
 Serial.println(" %");

 delay(2000);
}

void readData(){
 t = dht.readTemperature();
 h = dht.readHumidity();
}
