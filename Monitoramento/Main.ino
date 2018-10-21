#include <DHT.h>
#include <DHT_U.h>


#include <Adafruit_Sensor.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

#define ONE_WIRE_BUS 2
#define DHTPIN 3     
#define DHTTYPE DHT22  

const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

DHT dht(DHTPIN, DHTTYPE);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
    
int umiPin = A0; 
int luxPin = A1; 
float umiValue;  
float luxValue;
float airHum;
float airTemp;
float soilTemp;
int percent = 0;

void setup() {
  Serial.begin(9600);
  sensors.begin();
  dht.begin();
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  
}

void loop() {

  getTempAr();
  getUmidAr();
  getLux();
  getTempSolo();
  getUmidSolo();

  lcdPrint(airTemp,soilTemp,umiValue,airHum,luxValue);
  Serial.println("\n");
}

  

  

