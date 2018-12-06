#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <BH1750.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define ONE_WIRE_BUS 2
#define DHT_PIN 5    
#define DHT_TYPE DHT11
#define HUMIDITY_PIN A0


DHT dht(DHT_PIN, DHT_TYPE);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
BH1750 lightMeter;

WiFiClient client;

char ssid[] = "DIGITE A REDE";
char pass[] = "DIGITE A SENHA"; 
int keyIndex = 0;
char server[] = "ecodomo-api.herokuapp.com";

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  initSensors();
  initWiFi();
}

void loop() {
  Serial.println("Iniciando...");  
  Serial.println("--------------------------");
  String data_env = initEnvSensors();
  String data_soil = initSoilSensors();
  sendData(data_env, data_soil);
  delay(tempo(6));
}

void initSensors() {
  sensors.begin();
  Wire.begin(D3,D2);
  dht.begin();
  lightMeter.begin();
}

void initWiFi() {
  checkShield();
  connectWiFi();
}

void connectWiFi() {
  WiFi.begin(ssid,pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    delay(20000);
  }
  Serial.println("Connected to WiFi");
}

void sendData(String data_soil, String data_env) {
  Serial.println("--------------------------");
  Serial.println("Starting connection to server...");
  if (client.connect(server, 80)) {
    Serial.println("Connected to server!");
    client.print("POST /cupulas/cupula_cesar/data");
    client.print(data_soil);
    client.print(data_env);
    client.println(" HTTP/1.1");
    client.println("Host: ecodomo-api.herokuapp.com");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  }
  Serial.println("--------------------------");
  stopClient();
}

void printResponse() {
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
}

void stopClient() {
  if (!client.connected()) {
    Serial.println("Disconnecting from server.");
    client.stop();
    while (true);
  }
}

void checkShield() {
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }
}

String initEnvSensors() {
  Serial.println("AMBIENTE: ");
  String temperature = String(getEnvTemperature());
  String humidity = String(getEnvHumidity());
  String luminosity = String(getLuminosity());
  String data_env = "?temperature_env=" + temperature + "&humidity_env=" + humidity + "&luminosity=" + luminosity;
  return data_env;
}

String initSoilSensors() {
  Serial.println("\nSOLO: ");
  String temperature = String(getSoilTemperature());
  String humidity = String(getSoilHumidity());
  String data_soil = "&temperature_soil=" + temperature + "&humidity_soil=" + humidity;
  return data_soil;
}

float getEnvTemperature() {
  float temperature = dht.readTemperature();
  Serial.println("Temperatura: " + String(temperature));
  return temperature;
}

float getEnvHumidity() {
  float humidity = dht.readHumidity();
  Serial.println("Umidade: " + String(humidity) + "%");
  return humidity;
}


float getLuminosity() {
  uint16_t luminosity = lightMeter.readLightLevel();
  Serial.println("Luminosidade: " + String(luminosity) + " Lumens");
  return luminosity;
  
}
  
float getSoilTemperature() {
  sensors.requestTemperatures();
  float temperature =  sensors.getTempCByIndex(0);
  Serial.println("Temperatura: " + String(temperature) + " C");
  return temperature;
}

float getSoilHumidity() {
  float humidity = analogRead(HUMIDITY_PIN);
  humidity = map(humidity,1024,320,0,100);
  Serial.println("Umidade: " + String(humidity) + "%");
  return humidity;
}

int tempo(int horas){
  int zeit = horas * 60 * 60 * 1000;
  return 1000;
  }