#include "pico/stdlib.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

int main(void) {        // Consumes ~54-58 mA
    const uint LED_PIN = 21; 

    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(LED_PIN, 1);   // LED on
        sleep_ms(500);          // wait 500 ms
        gpio_put(LED_PIN, 0);   // LED off
        sleep_ms(500);
    }

    return 0; // never reached
}