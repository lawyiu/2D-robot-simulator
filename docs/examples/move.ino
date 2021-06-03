/*
    The L298N motor driver is controlled using six pins. Pins IN1 and IN2 are used to control the direction of the
    left motor. If IN1 is HIGH and IN2 is LOW, the motor will turn in one direction. If IN1 is LOW and IN2 is HIGH,
    the motor will turn in the other direction. Pins IN3 and IN4 operate in the same way except they control the
    right motor's direction. The ENA and ENB pins are used to control the speed of the left and right motors
    respectively using analogWrite which outputs a PWM signal on a PWM capable pin (pins marked by the ~ symbol).
*/

#define IN1_PIN 2
#define IN2_PIN 3
#define IN3_PIN 4
#define IN4_PIN 5

#define ENA_PIN 9
#define ENB_PIN 10

class RandomGenerator {
public:
    RandomGenerator(unsigned long seed) {
        x = seed;
    }

    int getRandom() {
        x = (a * x + c) % m;
        return x;
    }

private:
    unsigned long x;

    const unsigned long a = 1103515245L;
    const unsigned short c = 12345;
    const unsigned long m = 2147483648L;
};

void setupForward() {
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);
}

void setupBackward() {
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, HIGH);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, HIGH);
}

void turnLeft(bool backward) {
    if (!backward) {
        setupForward();
    } else {
        setupBackward();
    }

    analogWrite(ENA_PIN, 0);
    analogWrite(ENB_PIN, 200);
}

void turnRight(bool backward) {
    if (!backward) {
        setupForward();
    } else {
        setupBackward();
    }

    analogWrite(ENA_PIN, 200);
    analogWrite(ENB_PIN, 0);
}

void goForward() {
    setupForward();

    analogWrite(ENA_PIN, 200);
    analogWrite(ENB_PIN, 200);
}

void goBackward() {
    setupBackward();

    analogWrite(ENA_PIN, 200);
    analogWrite(ENB_PIN, 200);
}

void stop() {
    analogWrite(ENA_PIN, 0);
    analogWrite(ENB_PIN, 0);
}

RandomGenerator rng(millis());

void setup() {
    // put your setup code here, to run once:
    pinMode(IN1_PIN, OUTPUT);
    pinMode(IN2_PIN, OUTPUT);
    pinMode(IN3_PIN, OUTPUT);
    pinMode(IN4_PIN, OUTPUT);
    pinMode(ENA_PIN, OUTPUT);
    pinMode(ENB_PIN, OUTPUT);
}

void changeDirection() {
    unsigned int randValue = rng.getRandom() % 7;

    switch (randValue) {
        case 0:
            turnLeft(false);
            break;

        case 1:
            turnLeft(true);
            break;

        case 2:
            turnRight(false);
            break;

        case 3:
            turnRight(true);
            break;

        case 4:
            goForward();
            break;

        case 5:
            goBackward();
            break;

        case 6:
            stop();
        default:
            break;
    }
}

void loop() {
    // put your main code here, to run repeatedly:
    static unsigned long prevMillis = 0;
    unsigned long currMillis = millis();
    if (currMillis - prevMillis > 1000) {
        prevMillis = currMillis;
        changeDirection();
    }
}
