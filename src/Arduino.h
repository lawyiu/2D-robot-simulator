#ifndef ARDUINO_HPP
#define ARDUINO_HPP

#include <bitset>
#include <iomanip>
#include <sstream>
#include <stddef.h>
#include <string>

#include "export.hpp"
#include "pinDirection.hpp"

enum { LOW, HIGH };

enum { BIN, HEX, DEC, OCT };

void pinMode(uint8_t pin, uint8_t mode);
int digitalRead(uint8_t pin);
void digitalWrite(uint8_t pin, uint8_t val);
int analogRead(uint8_t pin);
void analogWrite(uint8_t pin, int val);

class SerialPort {
public:
    void begin(unsigned long rate);

    size_t print(const char* str);
    size_t print(char val, int type = DEC);
    size_t print(unsigned char val, int type = DEC);
    size_t print(int val, int type = DEC);
    size_t print(unsigned int val, int type = DEC);
    size_t print(double val, int places);

    size_t println(const char* str);
    size_t println(char val, int type = DEC);
    size_t println(unsigned char val, int type = DEC);
    size_t println(int val, int type = DEC);
    size_t println(unsigned int val, int type = DEC);
    size_t println(double val, int places);

private:
    template <typename T> std::string formatVal(T val, int type);

    bool mBegan;
};

#include "Arduino.tcc"

extern SerialPort Serial;
extern SerialPort Serial1;
extern SerialPort Serial2;
extern SerialPort Serial3;

unsigned long millis();

extern "C" {
    EXPORT void setup();
    EXPORT void loop();
}

#endif /* ARDUINO_HPP */
