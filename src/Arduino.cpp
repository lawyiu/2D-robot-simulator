#include "Arduino.h"
#include "app.hpp"

#include <iostream>
#include <string.h>

SerialPort Serial;
SerialPort Serial1;
SerialPort Serial2;
SerialPort Serial3;

void SerialPort::begin(unsigned long rate) {
    mBegan = true;
}

size_t SerialPort::print(const char* str) {
    if (!mBegan) {
        std::cout << "Serial.begin was not called!\r\n";
        return 0;
    }

    std::cout << str;

    return strlen(str);
}

size_t SerialPort::print(char val, int type) {
    return print(formatVal<char>(val, type).c_str());
}

size_t SerialPort::print(unsigned char val, int type) {
    return print(formatVal<unsigned char>(val, type).c_str());
}
size_t SerialPort::print(int val, int type) {
    return print(formatVal<int>(val, type).c_str());
}

size_t SerialPort::print(unsigned int val, int type) {
    return print(formatVal<unsigned int>(val, type).c_str());
}

size_t SerialPort::print(double val, int places) {
    std::ostringstream os;
    os << std::fixed << std::setprecision(places) << val;

    return print(os.str().c_str());
}

size_t SerialPort::println(const char* str) {
    std::ostringstream os;
    os << str << "\r\n";
    return print(os.str().c_str());
}

size_t SerialPort::println(char val, int type) {
    return println(formatVal(val, type).c_str());
}

size_t SerialPort::println(unsigned char val, int type) {
    return println(formatVal(val, type).c_str());
}

size_t SerialPort::println(int val, int type) {
    return println(formatVal(val, type).c_str());
}

size_t SerialPort::println(unsigned int val, int type) {
    return println(formatVal(val, type).c_str());
}

size_t SerialPort::println(double val, int places) {
    size_t numPrinted = print(val, places);
    numPrinted += print("\r\n");

    return numPrinted;
}

unsigned long millis() {
    return App::getInstance().millis();
}
