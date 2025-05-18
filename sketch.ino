#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define boardLED 2 // LED onboard

// Identificadores
const char* ID        = "lucas";
const char* moduleID  = "esp32-lucas";

// Wi-Fi
const char* SSID      = "Wokwi-GUEST";
const char* PASSWORD  = "";

// MQTT Broker
const char* BROKER_MQTT  = "172.174.44.83";
const int   BROKER_PORT  = 1883;
const char* mqttUser     = "admin";
const char* mqttPassword = "SENHA_AQUI"; // <<< Substitua pela senha

#define TOPICO_PUBLISH  "fiap/iot/lucas"

WiFiClient espClient;
PubSubClient MQTT(espClient);
char buffer[256];

void initWiFi() {
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void reconectaWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Reconectando Wi-Fi...");
    initWiFi();
  }
}

void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  while (!MQTT.connected()) {
    Serial.println("Conectando ao Broker MQTT...");
    if (MQTT.connect(moduleID, mqttUser, mqttPassword)) {
      Serial.println("Conectado ao Broker!");
    } else {
      Serial.print("Falha na conexão. Estado: ");
      Serial.println(MQTT.state());
      delay(2000);
    }
  }
}

void verificaConexoesWiFiEMQTT() {
  reconectaWiFi();
  if (!MQTT.connected()) {
    initMQTT();
  }
  MQTT.loop();
}

void enviaEstadoOutputMQTT() {
  MQTT.publish(TOPICO_PUBLISH, buffer);
  Serial.println("Mensagem publicada com sucesso!");
}

void piscaLed() {
  digitalWrite(boardLED, HIGH);
  delay(300);
  digitalWrite(boardLED, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(boardLED, OUTPUT);
  digitalWrite(boardLED, LOW);
  initWiFi();    
  initMQTT();
}

void loop() {
  verificaConexoesWiFiEMQTT();

  StaticJsonDocument<300> doc;
  doc["ID"] = ID;
  doc["Sensor"] = moduleID;
  doc["IP"] = WiFi.localIP().toString();
  doc["Temperatura"] = random(200, 350) / 10.0;
  doc["Umidade"] = random(400, 800) / 10.0;
  doc["Pressao"] = random(980, 1050);
  doc["Altitude"] = random(0, 500);

  serializeJson(doc, buffer);
  Serial.println(buffer);
  enviaEstadoOutputMQTT();
  piscaLed();
  delay(10000);
}
