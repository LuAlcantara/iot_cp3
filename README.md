# Projeto IoT - Comunicação MQTT com ESP32 (Wokwi + Azure)

Este projeto simula o envio de dados de sensores via MQTT utilizando um ESP32 virtual no [Wokwi](https://wokwi.com), se conectando a uma máquina virtual hospedada na Azure com Mosquitto e Node-RED.

## ✅ Funcionalidades
- Conexão Wi-Fi simulada
- Envio de dados simulados (temperatura, umidade, pressão, altitude)
- Mensagens publicadas no tópico MQTT: `fiap/iot/lucas`
- Integração com Node-RED para visualização

## ⚙️ Infraestrutura utilizada
- **ESP32** simulado no Wokwi
- **Broker Mosquitto** instalado em VM Ubuntu (Azure)
- **Node-RED** para recebimento e visualização das mensagens
- **MQTT autenticado** com usuário e senha

## 🚧 Importante
Por segurança, a senha real do usuário MQTT foi removida do código.  
Para testar localmente, **substitua a string `SENHA_AQUI`** no campo `mqttPassword` pela sua senha real:

```cpp
const char* mqttPassword = "SUA_SENHA_REAL";
