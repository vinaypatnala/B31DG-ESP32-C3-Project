#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_rom_sys.h"  // For esp_rom_delay_us()

#define PB1 5   // Push Button 1 (Enable Output)
#define PB2 6   // Push Button 2 (Toggle Mode)
#define DATA 2  // DATA Signal Output (Green LED)
#define SYNC 10 // SYNC Signal Output (Red LED)

int a = 1100;  // TON(1) in µs
int b = 2600;  // OFF time in µs
int c = 11;    // Pulses per cycle
int d = 6500;  // Idle time in µs

bool enable_output = false;
bool select_waveform = false;

// Button state tracking for edge detection
bool prev_pb1_state = false;
bool prev_pb2_state = false;

// Task handle for waveform execution
TaskHandle_t waveformTaskHandle = NULL;

// Function for microsecond delay
void delay_us(uint32_t microseconds) {
    esp_rom_delay_us(microseconds);
}

// GPIO Configuration
void configure_gpio() {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << PB1) | (1ULL << PB2),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,  // Enable pull-up to avoid floating states
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    gpio_config_t output_conf = {
        .pin_bit_mask = (1ULL << DATA) | (1ULL << SYNC),
        .mode = GPIO_MODE_OUTPUT,
    };
    gpio_config(&output_conf);
}

// **FreeRTOS Task for Normal Waveform**
void normal_waveform_task(void *pvParameters) {
    while (1) {
        if (!enable_output) {
            gpio_set_level(DATA, 0);
            gpio_set_level(SYNC, 0);
            ESP_LOGI("WAVEFORM", "Output Disabled - DATA and SYNC LOW");
            vTaskDelay(pdMS_TO_TICKS(100));  // Avoid CPU overuse
            continue;
        }

        gpio_set_level(SYNC, 1);
        delay_us(50);
        gpio_set_level(SYNC, 0);

        for (int i = 0; i < c; i++) {
            gpio_set_level(DATA, 1);
            ESP_LOGI("WAVEFORM", "DATA HIGH - Pulse %d", i + 1);
            delay_us(a + (i * 50));

            gpio_set_level(DATA, 0);
            delay_us(b);
        }
        delay_us(d);
    }
}

// **FreeRTOS Task for Alternative Waveform**
void alternative_waveform_task(void *pvParameters) {
    while (1) {
        if (!enable_output) {
            gpio_set_level(DATA, 0);
            gpio_set_level(SYNC, 0);
            ESP_LOGI("WAVEFORM", "Output Disabled - DATA and SYNC LOW");
            vTaskDelay(pdMS_TO_TICKS(100));  // Allow other tasks to run
            continue;
        }

        gpio_set_level(SYNC, 1);
        esp_rom_delay_us(50);  // Short delay does not affect WDT
        gpio_set_level(SYNC, 0);

        for (int i = 0; i < c; i++) {
            gpio_set_level(DATA, 1);
            ESP_LOGI("WAVEFORM", "DATA HIGH - Pulse %d", i + 1);
            esp_rom_delay_us(a + ((c - i - 1) * 50));  // Decreasing Pulse Width

            gpio_set_level(DATA, 0);
            esp_rom_delay_us(b);
        }
        esp_rom_delay_us(d);

        vTaskDelay(pdMS_TO_TICKS(1));  // **Yield to prevent watchdog resets**
    }
}
// **Function to Start the Appropriate Waveform Task**
void start_waveform_task() {
    if (waveformTaskHandle != NULL) {
        vTaskDelete(waveformTaskHandle);
        waveformTaskHandle = NULL;
    }

    if (select_waveform) {
        xTaskCreate(alternative_waveform_task, "alternative_waveform", 4096, NULL, 1, &waveformTaskHandle);
        ESP_LOGI("TASK", "Alternative waveform task started");
    } else {
        xTaskCreate(normal_waveform_task, "normal_waveform", 4096, NULL, 1, &waveformTaskHandle);
        ESP_LOGI("TASK", "Normal waveform task started");
    }
}

// **Main Application**
void app_main() {
    configure_gpio();
    ESP_LOGI("ESP32", "Waveform Generator Started");

    while (1) {
        // **Edge Detection for PB1 (Enable/Disable Output)**
        bool curr_pb1_state = gpio_get_level(PB1);
        if (curr_pb1_state && !prev_pb1_state) {  // Detects only new button press
            enable_output = !enable_output;
            ESP_LOGI("BUTTON", "PB1 Pressed - Output %s", enable_output ? "Enabled" : "Disabled");
            start_waveform_task();
        }
        prev_pb1_state = curr_pb1_state;  // Update previous state

        // **Edge Detection for PB2 (Toggle Waveform Mode)**
        bool curr_pb2_state = gpio_get_level(PB2);
        if (curr_pb2_state && !prev_pb2_state) {  // Detects only new button press
            select_waveform = !select_waveform;
            ESP_LOGI("BUTTON", "PB2 Pressed - Mode: %s", select_waveform ? "Alternative" : "Normal");
            start_waveform_task();
        }
        prev_pb2_state = curr_pb2_state;  // Update previous state

        vTaskDelay(pdMS_TO_TICKS(50));  // **Shorter Delay for Responsive Button Presses**
    }
}
