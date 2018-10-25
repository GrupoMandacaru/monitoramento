#include <SPI.h>
#include <WiFi.h>

char ssid[] = "GNED";
char pass[] = "bemvindosaogned"; 
int keyIndex = 0;
int status = WL_IDLE_STATUS;
char server[] = "ecodomo-api.herokuapp.com";

WiFiClient client;

void initWiFi() {
  checkShield();
  connectWiFi();
}

void connectWiFi() {
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(20000);
  }
  Serial.println("Connected to WiFi");
}

void sendData(String data_soil, String data_env) {
  Serial.println("--------------------------");
  Serial.println("Starting connection to server...");
  if (client.connect(server, 80)) {
    Serial.println("Connected to server!");
    client.print("POST /cupulas/cupula_x/data");
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
