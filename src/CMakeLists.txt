# This is the main binary. List your C files here.
add_executable(blink
    blink.c
    )

add_executable(blink_task
    blink_task.c
    )

add_executable(alarm
    hello_sleep_alarm.c
    )

add_executable(hello_dormant_gpio
        hello_dormant_gpio.c
        )

pico_set_program_name(blink "test")
pico_set_program_version(blink "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(blink 0)
pico_enable_stdio_usb(blink 1)

pico_enable_stdio_uart(blink_task 1)
pico_enable_stdio_usb(blink_task 0)

# Add the libraries to the build
target_link_libraries(blink PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
)

target_link_libraries(blink_task PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
)

target_link_libraries(alarm
  pico_stdlib
  pico_multicore
  hardware_sleep
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
)

target_link_libraries(hello_dormant_gpio
  pico_stdlib
  hardware_sleep
  )
  pico_add_extra_outputs(hello_dormant_gpio)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    # For led support on pico_w
    target_link_libraries(blink PRIVATE
        pico_cyw43_arch_none
    )
endif()

if(PICO_CYW43_SUPPORTED)
    # For led support on pico_w
    target_link_libraries(blink_task PRIVATE
        pico_cyw43_arch_none
    )
endif()

# Another pico macro which generates the uf2 file in addition to the elf
pico_add_extra_outputs(blink)

find_program(OPENOCD openocd)
find_program(PICOTOOL picotool)

add_custom_target(flash ${PICOTOOL} load -f $<TARGET_FILE:blink> DEPENDS blink)
add_custom_target(flash_task ${PICOTOOL} load -f $<TARGET_FILE:blink_task> DEPENDS blink_task)
add_custom_target(flash_alarm ${PICOTOOL} load -f $<TARGET_FILE:alarm> DEPENDS alarm)
add_custom_target(flash_dormant ${PICOTOOL} load -f $<TARGET_FILE:hello_dormant_gpio> DEPENDS hello_dormant_gpio)

add_custom_target(openocd_flash ${OPENOCD} -s ${OPENOCD_PATH} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c 'adapter speed 5000; program "$<TARGET_FILE:blink>" verify reset exit' DEPENDS blink)

add_custom_target(flash_alarm_openocd
  COMMAND ${OPENOCD} -s ${OPENOCD_PATH}
          -f interface/cmsis-dap.cfg
          -f target/rp2040.cfg
          -c "adapter speed 5000"
          -c "init"
          -c "reset halt"
          -c "program {$<TARGET_FILE:alarm>} verify reset exit"
  DEPENDS alarm
  USES_TERMINAL
)
