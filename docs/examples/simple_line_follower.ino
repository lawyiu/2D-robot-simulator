/*
    The L298N motor driver is controlled using six pins. Pins IN1 and IN2 are used to control the direction of the
    left motor. If IN1 is HIGH and IN2 is LOW, the motor will turn in one direction. If IN1 is LOW and IN2 is HIGH,
    the motor will turn in the other direction. Pins IN3 and IN4 operate in the same way except they control the
    right motor's direction. The ENA and ENB pins are used to control the speed of the left and right motors
    respectively using analogWrite which outputs a PWM signal on a PWM capable pin (pins marked by the ~ symbol).
*/

// L298N Motor Driver pins
#define IN1_PIN 2
#define IN2_PIN 3
#define IN3_PIN 4
#define IN4_PIN 5

#define ENA_PIN 9
#define ENB_PIN 10

// Line sensor input pins
#define LINE_L_PIN 6 // Left
#define LINE_C_PIN 7 // Center
#define LINE_R_PIN 8 // Right

void setupForward() {
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);
}

void turnLeft() {
    analogWrite(ENA_PIN, 0);
    analogWrite(ENB_PIN, 180);
}

void turnRight() {
    analogWrite(ENA_PIN, 180);
    analogWrite(ENB_PIN, 0);
}

void goForward() {
    setupForward();

    analogWrite(ENA_PIN, 180);
    analogWrite(ENB_PIN, 180);
}

void stop() {
    analogWrite(ENA_PIN, 0);
    analogWrite(ENB_PIN, 0);
}

void setup() {
    // put your setup code here, to run once:
    // L298N Motor Driver pins setup
    pinMode(IN1_PIN, OUTPUT);
    pinMode(IN2_PIN, OUTPUT);
    pinMode(IN3_PIN, OUTPUT);
    pinMode(IN4_PIN, OUTPUT);
    pinMode(ENA_PIN, OUTPUT);
    pinMode(ENB_PIN, OUTPUT);

    // Line sensor pins default to INPUT so no need to change their mode

    goForward();
}

void loop() {
    // put your main code here, to run repeatedly:
    bool left = digitalRead(LINE_L_PIN);
    bool center = digitalRead(LINE_C_PIN);
    bool right = digitalRead(LINE_R_PIN);

    if (left) {
        turnLeft();
    }
    if (right) {
        turnRight();
    }
}
