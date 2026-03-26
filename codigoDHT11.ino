//________________
//DHT11
//________________
#include <Wifi.h>
#include <HTTPClient.h>
#include "DHT.h"

//DHT
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// CONEXÃO DE WIFI
const char* ssid = "nome da rede";
const char* password = "senha";

//Ip SERVER
const char* serverIP = "192.168.1.0"; /*altera o IP conforme o 1° circuito*/

//controle de canal
unsigned long lastSend = 0;
const long interval = 5000; //5 segs

bool wifiConnected = false;

//----------------------
//WIFI
//----------------------
bool connectWifi(){
  Serial.println("\n[WIFI]Resetando a interface.....");
  Wifi.disconnected(true);
  delay(1000)
  Wifi.mode(WIFI_STA);
  Wifi.begin(ssid, password);
  Serial.println("\n[WIFI]conectando.....");
  Serial.println("\n[WIFI]ssid:  ");
  Serial.println](ssid);

  int tentativas = 0;
  while(Wifi.status() !=WL_CONNECTED && tentativas < 20){
    delay(500);
    Serial.println(".");
    tentativas++;
  }

  if(Wifi.status()== WL_CONNECTED){
    Serial.println("\n[WIFI] Conectando!");
    Serial.println("[WIFI]: ");
    Serial.println(Wifi.localIP());

    return true;
  }else{
    Seria.println("\n[WIFI] Falha na conexão");
    return false;
  }
}
//_________________
// Envio HTTP
//_________________
void sendData(float temp, float hum){

  HTTPClient http;

  String url = "http://"+ String(serverIP) +
              "/update?temp=" + String(temp,1) +
              "&hum" + String(hum,1);

  Serial.println("[HTTP]Enviando: ");
  Serial.println(url);
  http.begin(url);
  http.setTimeout(3000); // 3 segs

  int httpCode = http.GET();
  if (httpCode > 0){
    Serial.println("[HTTP]Resposta: ");
    Serial.println(httpCode);
  }
  http.end();
  
}


