# Smart Waste Management System — Project Report

## 1. Introduction

The Smart Waste Management System is an IoT-based bin monitoring prototype designed to estimate waste-bin fill level and provide local and remote status information.

## 2. Objective

To monitor the fill level of a waste bin using an ultrasonic sensor and communicate the measured status through an ESP32 and MQTT.

## 3. Hardware

The prototype uses an ESP32 DevKit, HC-SR04 ultrasonic sensor, SSD1306 OLED, three LEDs and a buzzer.

## 4. Working Principle

The HC-SR04 measures the distance from the sensor to the waste surface. The firmware uses a configured bin height of 30 cm to calculate the approximate fill percentage.

Formula:

```text
Fill (%) = ((Bin Height - Distance) / Bin Height) × 100
```

The calculated value is constrained to the 0–100% range.

## 5. Status Logic

- Below 40% → LOW → Green LED
- 40% to below 80% → MEDIUM → Yellow LED
- 80% or above → FULL → Red LED + buzzer

## 6. IoT Communication

The ESP32 connects to Wi-Fi and publishes JSON data to:

```text
smartbin/bin001/data
```

The configured publishing interval is 5 seconds.

## 7. Display

The OLED shows the project title, measured distance, fill percentage and current status.

## 8. Simulation

A Wokwi simulation is included in `simulation/wokwi/diagram.json`.

## 9. Security

Credentials must remain private and should never be committed to the public repository.

## 10. Future Scope

The prototype can be extended with multiple bins, location tracking, cloud storage, dashboards, route optimization, low-power operation and long-range wireless communication.
