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
  delay(21600000);
}
  
