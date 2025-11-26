// #pragma GCC optimize ("O0")

#include <stdio.h>
#include "pico/stdlib.h"
#include <pico/sync.h>
#include "FreeRTOS.h"
#include "task.h"

#define LED_PIN 21
#define IN_PIN 2
#define OUT_PIN LED_PIN

int toggle = 1; 

void vBlinkTask(void *blink){
    (void)blink;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // cyw43_arch_init();
    
    for (;;) {
        // Scenario 2

        gpio_put(LED_PIN, 1);

        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_put(LED_PIN, 0);

        vTaskDelay(pdMS_TO_TICKS(500));

        // Scenario 3

        // while(1) {
        //     uint32_t k;
        //     for (int i = 0; i < 30; i++) {
        //         uint32_t j = 0;
        //         j = ((~j >> i) + 1) * 27644437;
        //         k = j;
        //     }
        // }
        
    }
}

void irq_callback(uint gpio, uint32_t event_mask)
{
    if (gpio != IN_PIN) return;
    toggle = !toggle;
    if (event_mask & GPIO_IRQ_EDGE_RISE) {
        gpio_put(OUT_PIN, true);
    } else if (event_mask & GPIO_IRQ_EDGE_FALL) {
        gpio_put(OUT_PIN, false);
    }
}

int main() {    // Thread w/ vTaskDelay comumes 0.13 W, 0.045 A at 3.0V
                // Thread w/ busy loop consumes 0.11 W, 0.036 A at 3.0V
                // IRQ 1KHz consumes 0.14 W, 0.049 A, at 3.0V
                // IRQ 1MHz consumes 0.18 W, 0.06A at 3.0V
                // Sleep comsumes 0.09W, 0.031A at 3.0V
                // Dormant consumes <0.01W, 0.002 at 3.0V
    stdio_init_all();

    gpio_init(IN_PIN);
    gpio_set_dir(IN_PIN, GPIO_IN);

    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    gpio_put(OUT_PIN, toggle);

    gpio_set_irq_enabled_with_callback(IN_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL , true, irq_callback);
    while(1) __wfi();
    return 0;

    // xTaskCreate(
    //     vBlinkTask,"Blink Task",256, NULL, 1, NULL
    // );

    // vTaskStartScheduler();
}