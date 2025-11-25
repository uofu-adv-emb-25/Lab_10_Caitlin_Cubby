#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"



#ifndef PICO_DEFAULT_LED_PIN
#define LED_PIN 25
#else
#define LED_PIN PICO_DEFAULT_LED_PIN
#endif

void vBlinkTask(void *blink){
    (void)blink;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    cyw43_arch_init();
    
    for (;;) {
        gpio_put(LED_PIN, 1);

        vTaskDelay(pdMS_TO_TICKS(250));

        gpio_put(LED_PIN, 0);

        vTaskDelay(pdMS_TO_TICKS(250));
    }
}

int main() {
    stdio_init_all();

    xTaskCreate(
        vBlinkTask,"Blink Task",256, NULL, 1, NULL
    );

    vTaskStartScheduler();
}