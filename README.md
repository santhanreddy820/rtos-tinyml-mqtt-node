\# RTOS-Style Smart Sensor Node with TinyML \& MQTT (C, Dev-C++)



This project simulates an embedded smart sensor node using a lightweight RTOS-style scheduler written in C.  

It runs on Windows (Dev-C++) with three periodic tasks:



\- \*\*Sensor Task\*\* – generates virtual temperature readings (20–80 °C).

\- \*\*ML Task\*\* – applies a TinyML-style linear decision model to classify each reading as `NORMAL` or `FAULT` and counts statistics.

\- \*\*Communication Task\*\* – publishes `TEMP` and `STATUS` messages to an MQTT topic (`smart/node`) using Eclipse Mosquitto.



Although it runs on a PC, the structure mimics a typical bare-metal embedded system with multiple cooperative tasks.



\## Features



\- Custom cooperative scheduler with millisecond periods for each task.

\- Simulated temperature sensor using pseudo-random values.

\- Lightweight anomaly detection model implemented as `y = w \* temp + b`.

\- Integration with Mosquitto MQTT (`mosquitto\_pub`) for telemetry publishing.

\- Designed so the scheduler and tasks can be ported to a real MCU later.



\## How to Build and Run (Dev-C++ on Windows)



1\. Open Dev-C++ and create a new \*\*C Console Application\*\* project.

2\. Replace the default `main.c` with `src/main.c` from this repository.

3\. Make sure Mosquitto is installed (Windows) and available at:

&nbsp;  `C:\\Program Files\\mosquitto\\mosquitto\_pub.exe`

4\. Compile \& run the program (F11).

5\. In a separate terminal, subscribe to the MQTT topic:



&nbsp;  ```bash

&nbsp;  "C:\\Program Files\\mosquitto\\mosquitto\_sub.exe" -t smart/node

You will see messages like:



TEMP=34,STATUS=NORMAL

TEMP=78,STATUS=FAULT



Possible Extensions



Replace the linear model with coefficients generated from a real ML model trained in Python.



Port the scheduler and tasks to STM32 / ESP32.



Add a UART/CLI-style command interface to tune thresholds at runtime.



Author



Dasari Santhan Reddy – B.Tech ECE, IIIT Kottayam

