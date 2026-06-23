# Firmware Rastreador Veicular ESP32 (MVP)

Este é o repositório inicial (MVP) do firmware de um rastreador veicular baseado no microcontrolador ESP32. 

O projeto foi projetado com uma **arquitetura modular** focada em facilitar a substituição de dados simulados (mocks) por hardwares e serviços reais em etapas futuras, especificamente focado na integração com o módulo celular e GNSS **SIM7070G**.

## 🚀 Arquitetura Atual

Nesta versão inicial (MVP), como o hardware final e o servidor ainda não estão disponíveis, os componentes críticos são simulados:

- **GPS Mock (`src/gps/`)**: Simula um módulo de GPS. Gera coordenadas (latitude e longitude) que incrementam progressivamente, além de valores de velocidade (0-100 km/h) e direção (0-360º) simulando um veículo em movimento contínuo.
- **Telemetria (`src/telemetry/`)**: Responsável por receber os dados do GPS e formatá-los em um payload JSON padronizado para envio ao backend.
- **Comunicação Mock (`src/communication/`)**: Simula a comunicação MQTT. Ao invés de conectar num broker real, o firmware imprime o payload JSON gerado na porta serial para fácil debug.
- **Armazenamento Mock (`src/storage/`)**: Simula o armazenamento offline que será utilizado quando houver queda de sinal celular. Atualmente, apenas realiza logs em memória simulando sucesso, mas já prepara o terreno para uso de memórias NVS no ESP32.
- **Máquina de Estados (`src/main.cpp`)**: Orquestra o ciclo do rastreador: 
  `GPS_ACTIVE` ➔ `TRANSMIT` ➔ `SLEEP` (Aguardando o próximo ciclo).

## 🛠️ Tecnologias Utilizadas

- **Microcontrolador**: ESP32
- **Framework**: Arduino (via PlatformIO)
- **Linguagem**: C++
- **Gerenciamento de JSON**: [ArduinoJson](https://arduinojson.org/)

## 📦 Estrutura do Projeto

```text
src/
├── main.cpp                  # Orquestração e máquina de estados
├── config/
│   └── config.h              # Configurações globais, pins e IDs
├── gps/
│   ├── gps.h                 # Interface para o GPS
│   └── gps_mock.cpp          # Implementação simulada de movimento
├── telemetry/
│   ├── telemetry.h           # Header do gerador de payload
│   └── telemetry.cpp         # Implementação de payload JSON
├── communication/
│   ├── mqtt.h                # Interface para comunicação remota
│   └── mqtt.cpp              # Simulação de envio via console
└── storage/
    ├── storage.h             # Interface para persistência offline
    └── storage.cpp           # Simulação de gravação de eventos
```

## ⚙️ Como Executar

Este projeto utiliza o [PlatformIO](https://platformio.org/).

1. Abra a pasta do projeto no VSCode com a extensão do PlatformIO instalada.
2. Para compilar o projeto:
   ```bash
   pio run
   ```
3. Para fazer upload do código para a placa ESP32:
   ```bash
   pio run -t upload
   ```
4. Para abrir o Monitor Serial e visualizar a simulação rodando e gerando os JSONs (115200 baud rate):
   ```bash
   pio device monitor
   ```

## 🛣️ Roadmap / Próximas Evoluções

- [ ] Adicionar conexão Wi-Fi provisória para testes reais em bancada.
- [ ] Substituir o Mock MQTT por envio real de telemetria a um broker na nuvem via Wi-Fi.
- [ ] Integrar leitura UART real do GPS físico (SIM7070G).
- [ ] Implementar comunicação MQTT com suporte a TLS/SSL nativa via chip SIM7070G (Modem Celular LTE/GPRS).
- [ ] Adicionar persistência usando a memória NVS do ESP32 para salvar payloads em caso de perda de conexão celular (Data Logger offline).
