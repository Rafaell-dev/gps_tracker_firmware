# Firmware Rastreador Veicular ESP32

Este repositório contém o firmware de um rastreador veicular IoT baseado no microcontrolador ESP32. O sistema é capaz de realizar a leitura de dados de geolocalização e telemetria através de um módulo GPS físico e enviá-los de forma segura para uma API REST na nuvem.

## 🚀 Funcionalidades Atuais

Nesta versão, o firmware realiza integração real de hardware e rede:

- **Integração de Hardware (GPS)**: Lê sentenças NMEA de um módulo GPS físico via porta Serial (UART) usando a biblioteca `TinyGPSPlus`. Coleta com precisão: latitude, longitude, altitude, velocidade, quantidade de satélites visíveis (HDOP) e timestamp exato (UTC/Epoch).
- **Processamento de Telemetria**: Organiza os dados coletados em um payload `JSON` otimizado e padronizado utilizando `ArduinoJson`.
- **Conectividade e Transmissão Segura**: Conecta-se à internet via **Wi-Fi** e realiza o envio da telemetria através de requisições **HTTP POST** para um endpoint remoto na nuvem. Suporta conexões **HTTPS/SSL** e autenticação via chave de API (`x-api-key`).

## 🛠️ Tecnologias Utilizadas

- **Microcontrolador**: ESP32
- **Framework**: Arduino (via PlatformIO)
- **Linguagem**: C++
- **Bibliotecas Principais**:
  - [ArduinoJson](https://arduinojson.org/) (Serialização de payloads)
  - [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) (Decodificação NMEA)
  - `WiFi`, `HTTPClient`, `WiFiClientSecure` (Comunicação de rede)

## 📦 Estrutura do Projeto

```text
src/
├── main.cpp                  # Máquina de estados e orquestração do ciclo principal
├── config/
│   └── config.h              # Configurações globais, pinos, credenciais e chaves
├── gps/
│   ├── gps.h                 # Interface para o GPS
│   └── gps.cpp               # Integração real via HardwareSerial 2
├── network/
│   ├── api_client.h          # Interface de comunicação web
│   └── api_client.cpp        # Conexão Wi-Fi e chamadas HTTP POST/HTTPS
└── telemetry/
    ├── telemetry.h           # Header do gerador de payload
    └── telemetry.cpp         # Montagem do pacote de dados em formato JSON
```

## ⚙️ A Máquina de Estados (Main Loop)

O funcionamento do rastreador é coordenado em `main.cpp` em um loop contínuo e não-bloqueante:
1. **Escuta Contínua**: Ouve a porta Serial do GPS aguardando novas coordenadas válidas.
2. **Intervalo Controlado**: Respeita um intervalo predefinido (`MAIN_LOOP_INTERVAL_MS`) antes de efetuar o próximo envio.
3. **Transmissão**: Quando o intervalo é atingido, o sistema gera o JSON de telemetria e o transmite via rede.

## 🚀 Como Executar

Este projeto utiliza o [PlatformIO](https://platformio.org/).

1. Clone o repositório e abra a pasta do projeto no VSCode (com a extensão do PlatformIO instalada).
2. Modifique os valores no arquivo `src/config/config.h` de acordo com a sua rede e credenciais (SSID, senha, API_URL, API_KEY).
3. Para compilar o projeto:
   ```bash
   pio run
   ```
4. Para fazer upload do código para a placa ESP32:
   ```bash
   pio run -t upload
   ```
5. Para abrir o Monitor Serial e visualizar os logs de execução (baud rate 115200):
   ```bash
   pio device monitor
   ```

## 🛣️ Próximos Passos (Roadmap)

- [ ] Substituir a comunicação atual Wi-Fi por um Módulo Celular LTE/GPRS (ex: SIM7070G) integrando MQTT com TLS/SSL nativo.
- [ ] Implementar sistema de Data Logger persistente (utilizando a memória NVS do ESP32 ou SD Card) para armazenar eventos offline (áreas de sombra) e reenviá-los quando a conexão retornar.
