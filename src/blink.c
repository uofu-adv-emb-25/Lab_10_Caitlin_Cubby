#include "pico/stdlib.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

int main(void) {        // Consumes ~54-58 mA
    const uint LED_PIN = 25; 

    stdio_init_all();
    cyw43_arch_init();

    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);   // LED on
        sleep_ms(500);          // wait 500 ms
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);   // LED off
        sleep_ms(500);
    }

    return 0; // never reached
}