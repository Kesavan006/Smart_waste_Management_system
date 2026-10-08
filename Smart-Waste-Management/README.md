# Smart Waste Management System

An IoT-based smart-bin monitoring system built around an **ESP32**, **HC-SR04 ultrasonic sensor**, **SSD1306 OLED**, three status LEDs, a buzzer, Wi-Fi and MQTT.

## Project Overview

The system measures the distance between the ultrasonic sensor and the waste surface, converts the measured distance into a bin fill percentage, displays the status locally, and publishes the readings through MQTT.

### Main functions

- ESP32-based monitoring
- HC-SR04 ultrasonic fill-level measurement
- 30 cm configured bin height
- OLED display for distance, fill percentage and status
- Green / yellow / red status indication
- Buzzer alert when the bin is full
- Wi-Fi connectivity
- Secure MQTT connection configuration for HiveMQ Cloud
- JSON sensor-data publishing
- Wokwi simulation

## System Logic

The configured thresholds are:

- **LOW:** fill < 40%
- **MEDIUM:** 40% to < 80%
- **FULL:** >= 80%

The controller publishes data every **5 seconds**.

Example MQTT payload:

```json
{
  "bin_id": "BIN001",
  "distance": 12.5,
  "fill": 58,
  "status": "MEDIUM"
}
```

MQTT topic:

```text
smartbin/bin001/data
```

## Hardware

| Component | Quantity | Purpose |
|---|---:|---|
| ESP32 DevKit | 1 | Main controller |
| HC-SR04 | 1 | Waste-level measurement |
| SSD1306 OLED | 1 | Local display |
| Green LED | 1 | Low fill indication |
| Yellow LED | 1 | Medium fill indication |
| Red LED | 1 | Full indication |
| Buzzer | 1 | Full-bin alert |

## Pin Configuration

| Component | ESP32 Pin |
|---|---|
| HC-SR04 TRIG | GPIO 5 |
| HC-SR04 ECHO | GPIO 18 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |
| Buzzer | GPIO 14 |
| Green LED | GPIO 25 |
| Yellow LED | GPIO 26 |
| Red LED | GPIO 27 |

These connections are taken from the supplied Wokwi simulation.

## Repository Structure

```text
Smart-Waste-Management/
├── README.md
├── src/
│   └── smart_waste_management.ino
├── circuit/
│   ├── circuit_diagram.png
│   └── wiring_diagram.png
├── hardware/
│   ├── components_list.md
│   └── pin_configuration.md
├── mqtt/
│   ├── mqtt_configuration.md
│   └── topic_structure.md
├── dashboard/
│   ├── dashboard_screenshot.png
│   └── README.md
├── images/
│   ├── prototype_placeholder.md
│   ├── hardware_setup_placeholder.md
│   └── working_demo_placeholder.md
├── documentation/
│   ├── block_diagram.png
│   ├── flowchart.png
│   └── project_report.md
├── simulation/
│   └── wokwi/
│       ├── diagram.json
│       └── README.md
├── data/
│   └── sample_sensor_data.csv
├── LICENSE
└── .gitignore
```

## Software / Libraries

Arduino IDE / Wokwi:

- ESP32 Arduino core
- WiFi
- WiFiClientSecure
- PubSubClient
- Wire
- Adafruit GFX Library
- Adafruit SSD1306 Library

## Running the Project

1. Open `src/smart_waste_management.ino`.
2. Install the required Arduino libraries.
3. Configure your Wi-Fi credentials.
4. Configure your private MQTT username/password.
5. Upload the code to an ESP32, or use the supplied Wokwi simulation.
6. Subscribe to `smartbin/bin001/data` using your MQTT client.
7. Monitor the OLED, LEDs and buzzer for local status.

## Security

**Do not upload real Wi-Fi or MQTT passwords to GitHub.**

The repository version intentionally contains placeholders. Keep real credentials in your local copy or another secure secret-management mechanism.

## Results

The system provides:

- Real-time distance measurement
- Calculated waste fill percentage
- Local visual status
- Audible full-bin alert
- MQTT-based remote data transmission

## Future Enhancements

- Multiple-bin monitoring
- GPS-based bin location
- Web/mobile dashboard
- Automatic collection-route optimization
- Cloud database and historical analytics
- Battery/solar power
- LoRaWAN for long-range communication
- Overfill and sensor-fault detection

## Author

**Kesavan S**  
ECE Student  
Anna University Regional Campus Coimbatore

