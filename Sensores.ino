#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
#define DHT_PIN 3     
#define DHT_TYPE DHT22
#define HUMIDITY_PIN A0
#define LUMINOSITY_PIN A1

DHT dht(DHT_PIN, DHT_TYPE);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void initSensors() {
  sensors.begin();
  dht.begin();
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
  int temp = 0;
  temp = analogRead(LUMINOSITY_PIN);
  float luminosity = (1.0/(float)temp)*750.0;
  Serial.println("Luminosidade: " + String(luminosity) + " Lumens");
  return luminosity;
  
}
  
float getSoilTemperature() {
  sensors.requestTemperatures();
  float temperature =  sensors.getTempCByIndex(0);
  Serial.println("Temperatura: " + String(temperature) + " C");
  return temperature;
}

int getSoilHumidity() {
  float humidity = analogRead(HUMIDITY_PIN);
  int percent = convertePorcentagem(humidity);
  Serial.println("Umidade: " + String(percent) + "%");
  return humidity;
}

int convertePorcentagem(int value)
{
  int valor = 0;
  valor = map(value, 550, 0, 0, 100);
  return valor;
}
