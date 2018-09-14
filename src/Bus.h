#ifndef BUS_H
#define BUS_H

#include <Arduino.h>

template <typename T>
class Bus {
private:
    byte pins[sizeof(T) * 8];
    
public:
    Bus(byte pins[sizeof(T) * 8]) {
        for (int i = 0; i < sizeof(T) * 8; i++) {
            //Serial.println(pins[i]);
            this->pins[i] = pins[i];
        }
        this->set_mode(INPUT_PULLUP);
    }
    
    void set_mode(byte mode) {
        for (int i = 0; i < sizeof(T) * 8; i++) {
            pinMode(this->pins[i], mode);
        }
    }
    
    void set(T data) {
        //this->set_mode(OUTPUT);
        for (int i = 0; i < sizeof(T) * 8; i++) {
            pinMode(this->pins[i], OUTPUT);
            digitalWrite(pins[i], data & 1);
            data >>= 1;
        }
    }
    
    T get() {
        T data = 0;
        for (int i = (sizeof(T) * 8) - 1; i >= 0; i--) {
            pinMode(this->pins[i], INPUT_PULLUP);
            data += digitalRead(this->pins[i]);
            if (i) {
                data <<= 1;
            }
        }
        return data;
    }
    
};

#endif
