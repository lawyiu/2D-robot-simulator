void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    Serial.println("Setup");
}

void loop() {
    // put your main code here, to run repeatedly:
    static unsigned long prevMillis = 0;
    unsigned long currMillis = millis();
    if (currMillis - prevMillis > 1000) {
        prevMillis = currMillis;
        Serial.println("Hello World!");
    }
}
