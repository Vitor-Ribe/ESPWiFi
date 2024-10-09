/*
    ESSE CÓDIGO TRANSFORMA A PLACA ESP8266 EM UM ACESS POINT, ONDE DISPOSITIVOS PODEM SE CONECTAR.
*/
#include <ESP8266WiFi.h>

const char *ssid = "MinhaRedeESP";  // Nome da rede Wi-Fi
const char *password = "12345678";  // Senha da rede Wi-Fi

void imprimirMAC(uint8_t* mac){
    for(int i=0; i<6; i++){
        if(i < 5) Serial.printf("%02X:", mac[i]);
        else Serial.printf("%02X", mac[i]);
    }
    Serial.println();
}

void setup() {
  Serial.begin(115200);
  // Configura o ESP8266 como ponto de acesso (AP)
  WiFi.softAP(ssid, password); //ssid, psk, channel, hidden, max_connection
  
  Serial.println();
  Serial.println("Ponto de acesso iniciado.");
  Serial.print("IP do AP: ");
  Serial.println(WiFi.softAPIP());  // Mostra o IP do ponto de acesso
  Serial.print("MAC do AP: ");
  Serial.println(WiFi.softAPmacAddress());  // Mostra o MAC do ponto de acesso
}

void loop() {
  // Dispositivos Conectados
  int numConexoes = WiFi.softAPgetStationNum();
  Serial.print("Dispositivos conectados: ");
  Serial.println(numConexoes);
  
  // MAC dos dispositivos conectados
  struct station_info *station = wifi_softap_get_station_info();
  while (station != NULL){
    Serial.print("Dispositivo conectado com MAC: ");
    imprimirMAC(station->bssid);
    station = STAILQ_NEXT(station, next);
  }
  delay(5000); // A cada 5s atualiza a lista
}
