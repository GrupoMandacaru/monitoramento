void header()
{
    DHT dht(DHTPIN, DHTTYPE);
    OneWire oneWire(ONE_WIRE_BUS);
    DallasTemperature sensors(&oneWire);
    
    int umiPin = A0; 
    int luxPin = A1; 
    int umiValue = 0;  
    float luxValue = 0;
    float airHum;
    float airTemp;
    int percent = 0;
}


void getTempAr()
{
  airTemp = dht.readTemperature();
  Serial.print("Temperatura Ar: ");
  Serial.println(airTemp);
  
}

void getUmidAr()
{
  airHum = dht.readHumidity();
  Serial.print("Umidade Ar: ");
  Serial.print(airHum);
  Serial.println("%");
  
}

void getLux()
{
  luxValue = (analogRead(luxPin)*39.0625);
  Serial.print("Luminosidade: ");
  Serial.print(luxValue);
  Serial.println(" Lumens");
}
  
void getTempSolo()
{
  sensors.requestTemperatures();
  Serial.print("Temperatura Solo: ");
  Serial.println(sensors.getTempCByIndex(0));
  soilTemp =  sensors.getTempCByIndex(0);
}

void getUmidSolo()
{
  umiValue = analogRead(umiPin);
  percent = convertePorcentagem(umiValue);
  Serial.print("Umidade Solo: ");
  Serial.print(percent);
  Serial.println("%");
}

int convertePorcentagem(int value)
{
  int valor = 0;
  valor = map(value, 550, 0, 0, 100);
  return valor;
}

void lcdPrint(float tempAr, float tempTerra, float umiAr, float umiTerra, float luz){

  lcd.clear();
  lcd.print("Temperatura Ar:");
  lcd.setCursor(0,1);
  lcd.print(tempAr);
  

  delay(4000);

  lcd.clear();
  lcd.print("Umidade Ar:");
  lcd.setCursor(0,1);
  lcd.print(umiAr);
  lcd.setCursor(4,1);
  lcd.print("%");

  delay(4000);
  
  lcd.clear();
  lcd.print("Temp. Solo:");
  lcd.setCursor(0,1);
  lcd.print(tempTerra);

  delay(4000);
  
  lcd.clear();
  lcd.print("Umidade Solo:");
  lcd.setCursor(0,1);
  lcd.print(umiTerra);
  lcd.setCursor(4,1);
  lcd.print("%");

  delay(4000);

  lcd.clear();
  lcd.print("Luminosidade:");
  lcd.setCursor(0,1);
  lcd.print(luz);
  lcd.setCursor(8,1);
  lcd.print("Lumens");

  delay(4000);
  
  }



