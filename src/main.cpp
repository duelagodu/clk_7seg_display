#include <Arduino.h>
#include <clk_7seg_display.h>

display my_display;

void setup() {

    int num[7] = {2, 3, 4, 5, 6, 7, 8};
    int dot = 9;
    int index[4] = {10, 11, 12, 13};

    my_display.set(num, dot, index);
}

void loop() {
    my_display.roll(100);
    
}

