# RTOS-Style Smart Sensor Node with TinyML & MQTT (C, Dev-C++)

This project is a simulation of an embedded smart sensor node built using a lightweight RTOS-style scheduler in C.  
It runs on Windows using Dev-C++ and demonstrates how periodic tasks work in a real-time embedded environment along with basic TinyML-based decision making and IoT communication.

The system consists of three main periodic tasks:

- **Sensor Task** – Simulates a temperature sensor and generates virtual readings in the range of 20–80 °C.  
- **ML Task** – Uses a TinyML-style linear decision model to classify each temperature reading as `NORMAL` or `FAULT` and maintains runtime statistics.  
- **Communication Task** – Publishes `TEMP` and `STATUS` data to an MQTT topic (`smart/node`) using Eclipse Mosquitto for remote monitoring.

Although executed on a PC, the overall structure closely resembles a real bare-metal embedded system using cooperative multi-tasking.

---

## Features

- Lightweight cooperative task scheduler with millisecond-level periodic execution.  
- Virtual temperature sensor with pseudo-random data generation.  
- Compact TinyML-inspired anomaly detection using a linear decision function.  
- MQTT-based telemetry transmission using Mosquitto (`mosquitto_pub`).  
- Modular design suitable for future porting to real microcontrollers such as STM32, ESP32, or AVR.

---

## How to Build and Run (Dev-C++ on Windows)

1. Open **Dev-C++** and create a new **C Console Application** project.  
2. Replace the default `main.c` file with `src/main.c` from this repository.  
3. Ensure that **Eclipse Mosquitto** is installed on your system and available at:

**C:\Program Files\mosquitto\mosquitto_pub.exe**

4. Compile and run the program using **F11**.  
5. Open a separate Command Prompt and subscribe to the MQTT topic using:

```bash
"C:\Program Files\mosquitto\mosquitto_sub.exe" -t smart/node
6. You will start receiving messages such as:
   TEMP=34,STATUS=NORMAL
   TEMP=78,STATUS=FAULT

**Possible Extensions**

Replace the handcrafted linear model with coefficients generated from a real machine learning model trained in Python.

Port the scheduler and task logic to real embedded hardware such as STM32 or ESP32.

Add a UART or CLI-style command interface to tune thresholds and parameters at runtime.

Log telemetry data into files or a cloud dashboard for analysis.

**Author**

Dasari Santhan Reddy
B.Tech – Electronics and Communication Engineering
IIIT Kottayam
