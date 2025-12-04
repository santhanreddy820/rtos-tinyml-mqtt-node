RTOS-Style Smart Sensor Node with TinyML & MQTT (C, Dev-C++)

This project is a simulation of an embedded smart sensor node built using a lightweight RTOS-style scheduler in C.
It runs on Windows using Dev-C++ and demonstrates how periodic tasks work in a real-time embedded environment along with basic TinyML-based decision making and IoT communication.

The system consists of three main periodic tasks:

Sensor Task – Simulates a temperature sensor and generates virtual readings in the range of 20–80 °C.
ML Task – Uses a TinyML-style linear decision model to classify each temperature reading as NORMAL or FAULT and maintains runtime statistics.
Communication Task – Publishes TEMP and STATUS data to an MQTT topic (smart/node) using Eclipse Mosquitto for remote monitoring.

Although executed on a PC, the overall structure closely resembles a real bare-metal embedded system using cooperative multi-tasking.

FEATURES

Lightweight cooperative task scheduler with millisecond-level periodic execution.

Virtual temperature sensor with pseudo-random data generation.

Compact TinyML-inspired anomaly detection using a linear decision function.

MQTT-based telemetry transmission using Mosquitto (mosquitto_pub).

Modular design suitable for future porting to real microcontrollers such as STM32, ESP32, or AVR.

HOW TO BUILD AND RUN (Dev-C++ on Windows)

Open Dev-C++ and create a new C Console Application project.

Replace the default main.c file with src/main.c from this repository.

Ensure that Eclipse Mosquitto is installed on your system and available at:

C:\Program Files\mosquitto\mosquitto_pub.exe

Compile and run the program using F11.

Open a separate Command Prompt and subscribe to the MQTT topic using:

"C:\Program Files\mosquitto\mosquitto_sub.exe" -t smart/node

You will start receiving messages such as:

TEMP=34,STATUS=NORMAL
TEMP=78,STATUS=FAULT

POSSIBLE EXTENSIONS

Replace the handcrafted linear model with coefficients generated from a real machine learning model trained in Python.

Port the scheduler and task logic to real embedded hardware such as STM32 or ESP32.

Add a UART or CLI-style command interface to tune thresholds and parameters at runtime.

Log telemetry data into files or a cloud dashboard for analysis.

AUTHOR

Dasari Santhan Reddy
B.Tech – Electronics and Communication Engineering
IIIT Kottayam
