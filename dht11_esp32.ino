#inclide <ArduinoJson.h>      // add ArduinoJson library v5.9.0
#include <Adafruit_Sensor.h>  // add Adafruit_Sensor library
#include <PubSubClient.h>     // add PubSubClient library
#include <DHT.h>        // add DHT library
#define DHTPIN 4        // define pin which is connected to DHT sensor
#define DHTTYPE DHT11   // define type of sensor, if you're another sensor change it

const char* ssid = "ssid";             // your wifi ssid
const char* password = "password";     // your wifi password
const char* mqttServer = "192.168.1.100";   // mqtt server address
const int mqttPort = 1883;                  // mqtt port
const char* mqttUser = "mqtt_username";     // your mqtt user
const char* mqttPassword = "mqtt_password"; // your mqtt password

float t;  // variable for temperature
float h;  // variable for humidity

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup()
{
Serial.begin(115200);
dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}
 
void loop() {
readPZEM();
    StaticJsonBuffer <300> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject();
    
    JSONencoder["device"] = "ESP32";
    JSONencoder["sensor type"] = "DHT11";
    JSONencoder["temperature"] = t;
    JSONencoder["humidity"] = h;

    char JSONmessageBuffer[100];
    JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println("Sending message to MQTT topic..");
    Serial.println(JSONmessageBuffer);
     
    if (client.publish("esp/dht11", JSONmessageBuffer) == true) {
      Serial.println("Success sending message");
    } else {
      Serial.println("Error sending message");
    }
    
    delay(2000);
    client.loop();
}

// function to read temperature and humidity 
void readData(){
 t = dht.readTemperature();
 h = dht.readHumidity();
}
