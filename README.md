# LAB 10 Caitlin & Cubby

![CMake](https://github.com/uofu-adv-emb-25/Lab_10_Caitlin_Cubby/actions/workflows/main.yml/badge.svg)

Cubby and Caitlin's implementation of LAB 10. Power consumption measurements are shown in the table below. Each process was allowed to settle for several seconds before the measurement was recorded. (All taken with supply at 3.0V)

## Power Results:

| Environment   | Power Draw    |
|:--------------|:-------------:|
| LED Blink     | 0.12 W        |   
| Blink (task)  | 0.13 W        |
| Busy loop     | 0.11 W        |
| IRQ 1KHz      | 0.14 W        |
| IRQ 1MHz      | 0.18 W        |
| Sleep         | 0.09 W        |
| Dormant       | <0.01 W       |
