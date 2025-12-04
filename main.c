#include <stdio.h>
#include <windows.h>   // Sleep(), GetTickCount()
#include <stdlib.h>    // rand(), system()
#include <time.h>      // time()

// ---- Global sensor value & stats ----
int g_temperature = 25;
unsigned long g_normal_count = 0;
unsigned long g_fault_count  = 0;

// ---- Task type ----
typedef void (*TaskFunc)(void);

typedef struct {
    TaskFunc func;
    unsigned int period_ms;
    unsigned long next_run_ms;
} Task;

// ---- Time helper (ms since start) ----
unsigned long millis(void) {
    static unsigned long start = 0;
    if (start == 0) {
        start = GetTickCount();
    }
    return GetTickCount() - start;
}

// ---- TinyML-style model ----
int is_fault(int temp) {
    /* y = w * temp + b
       if y > 0 -> FAULT
       else     -> NORMAL
    */
    float w = 0.25f;
    float b = -15.0f;

    float y = w * temp + b;
    return (y > 0.0f);   // 1 = FAULT, 0 = NORMAL
}

// ---- Tasks ----

// Simulated temperature sensor: 20–80 °C
void sensor_task(void) {
    g_temperature = 20 + rand() % 61;   // 20..80
    printf("[Sensor] Temp = %d C\n", g_temperature);
}

// ML task: classify and track stats
void ml_task(void) {
    int fault = is_fault(g_temperature);

    if (fault) {
        g_fault_count++;
        printf("[ML] TEMP=%d C -> STATUS=FAULT (anomaly detected) | total faults = %lu\n",
               g_temperature, g_fault_count);
    } else {
        g_normal_count++;
        printf("[ML] TEMP=%d C -> STATUS=NORMAL | total normals = %lu\n",
               g_temperature, g_normal_count);
    }
}

// Communication task: publish via mosquitto_pub.exe
void comm_task(void) {
    char cmd[512];
    int fault = is_fault(g_temperature);

    // Build command to call mosquitto_pub with full path
    // NOTE: path must match your installation path.
    snprintf(
        cmd,
        sizeof(cmd),
        "\"C:\\\\Program Files\\\\mosquitto\\\\mosquitto_pub.exe\" -t smart/node -m \"TEMP=%d,STATUS=%s\"",
        g_temperature,
        fault ? "FAULT" : "NORMAL"
    );

    printf("[COMM] Executing: %s\n", cmd);
    system(cmd);   // execute the command
}

// ---- Main with lightweight scheduler ----
int main(void) {
    Task tasks[3];
    int i;  // loop variable (C89 style)

    printf("Starting lightweight RTOS-style scheduler with MQTT...\n");

    // Seed RNG
    srand((unsigned int)time(NULL));

    // Configure tasks
    tasks[0].func        = sensor_task;
    tasks[0].period_ms   = 1000;  // 1s
    tasks[0].next_run_ms = 0;

    tasks[1].func        = ml_task;
    tasks[1].period_ms   = 1000;  // 1s
    tasks[1].next_run_ms = 0;

    tasks[2].func        = comm_task;
    tasks[2].period_ms   = 2000;  // 2s
    tasks[2].next_run_ms = 0;

    // Cooperative scheduler loop
    while (1) {
        unsigned long now = millis();

        for (i = 0; i < 3; i++) {
            if (now >= tasks[i].next_run_ms) {
                tasks[i].func();
                tasks[i].next_run_ms = now + tasks[i].period_ms;
            }
        }

        Sleep(10);  // avoid 100% CPU
    }

    return 0;
}

