#include "Arduino.h"

#define LED_PIN 13

bool on = false;

void setup() {
    // put your setup code here, to run once:
    pinMode(LED_PIN, OUTPUT);
}

void toggle() {
    if (on) {
        digitalWrite(LED_PIN, LOW);
    } else {
        digitalWrite(LED_PIN, HIGH);
    }

    on = !on;
}

void loop() {
    // put your main code here, to run repeatedly:
    static unsigned long prevMillis = 0;
    unsigned long currMillis = millis();
    if (currMillis - prevMillis > 1000) {
        prevMillis = currMillis;
        toggle();
    }
}
