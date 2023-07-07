#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define IO_USERNAME ""          
#define IO_KEY ""

// Configuração da rede WiFi
const char* ssid = "sala203";
const char* password = "s@l@203#";

// Configurações do broker MQTT
const char* mqttserver = "34.28.96.89";
const int mqttport = 1883;
const char* mqttUser = IO_USERNAME;
const char* mqttPassword = IO_KEY;

const int dhtPin = 23;
const int buttonPin = 33; 
const int ledPin = 32; 
int buzzer = 5;
String comando = "";
char s_bot[4];
int statusBot = 0;

DHT dht(dhtPin, DHT11);

// Instância do cliente WiFi
WiFiClient espClient;

// Instância do cliente MQTT
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);  
  dht.begin(); 
  pinMode(buttonPin, INPUT); 
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);

// Conexão com a rede WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi!");

  // Conexão ao servidor MQTT
  client.setServer(mqttserver, mqttport);
  client.setCallback(callback);  // Define a função de callback para tratar os comandos recebidos
  while (!client.connected()) {
    Serial.println("Conectando ao broker MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword)){
    //if (client.connect("ESP32Client")){
      Serial.println("Conectado ao broker MQTT!");
    } else {
      Serial.print("Falha na conexão. Código de erro: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}


void loop() {
    // Verificação e reconexão ao broker MQTT, se necessário
    if (!client.connected()) {
      reconnect();
    }

    // Verifica se há algum pacote MQTT para ser processado
    client.loop();

    float temperatura = dht.readTemperature();
    float umidade = dht.readHumidity();
    int buttonState = digitalRead(buttonPin);
    //Serial.println(buttonState);
 
    if (buttonState == LOW) { 
      Serial.print("Temperatura: ");
      Serial.println(temperatura);
      Serial.print("Umidade: ");
      Serial.println(umidade);
      delay(10000);

      // Publicação da temperatura e Umidade no tópico "temperatura" e "umidade"
      String tempString = String(temperatura);
      char charTemp[tempString.length() + 1];
      tempString.toCharArray(charTemp, tempString.length() + 1);
      client.publish("aparecidalm/feeds/temperatura", charTemp);
      delay(10000);
      String umiString = String(umidade);
      char charUmi[umiString.length() + 1];
      umiString.toCharArray(charUmi, umiString.length() + 1);
      client.publish("aparecidalm/feeds/umidad", charUmi);

      if(temperatura >= 30.00 && umidade >=70.00){
        Serial.println("Atenção! Condição do Ambiente Alterada!");
        digitalWrite(ledPin, HIGH);  
        digitalWrite(buzzer, HIGH);
        delay(10000);
        // String statusString = String(buzzer);
        // char charStatus[statusString.length() + 1];
        // statusString.toCharArray(charStatus, statusString.length() + 1);
        // client.publish("aparecidalm/feeds/buzzer", charStatus);

      }else {
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzer, LOW);
        Serial.println("Condições do Ambiente Normal!");
        delay(10000);
        // String statusString = String(buzzer);
        // char charStatus[statusString.length() + 1];
        // statusString.toCharArray(charStatus, statusString.length() + 1);
        // client.publish("aparecidalm/feeds/buzzer", charStatus);
      }
    }else{
       dtostrf(statusBot,1,1,s_bot);
       Serial.print("Status Botão: ");
       Serial.println(statusBot);
       client.publish("aparecidalm/feeds/botao", s_bot);
       Serial.println("Atenção! Disparo Manual!");
       digitalWrite(ledPin, HIGH);
       digitalWrite(buzzer, HIGH);
       delay(10000);

      // String statusString = String(buzzer);
      // char charStatus[statusString.length() + 1];
      // statusString.toCharArray(charStatus, statusString.length() + 1);
      // client.publish("aparecidalm/feeds/buzzer", charStatus);
    }      

}

// Função para reconexão ao broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.println("Tentando reconectar ao broker MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
   //  if (client.connect("ESP32Client")) {
      Serial.println("Reconectado ao broker MQTT!");
      //client.subscribe("led1");
      client.subscribe("aparecidalm/feeds/temperatura");
    } else {
      Serial.print("Falha na conexão. Código de erro: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

// Função de callback para tratar os comandos recebidos
void callback(char* topic, byte* payload, unsigned int length) {
  // Converte o payload em uma string
  String command = "";
  for (int i = 0; i < length; i++) {
    command += (char)payload[i];
  }
  comando = command;
  // Verifica o tópico e o comando recebido
  if (String(topic) == "status") {
    if (command == "1") {
      
    } else if (command == "2") {
    
    } else {
    
    }
  }
}
