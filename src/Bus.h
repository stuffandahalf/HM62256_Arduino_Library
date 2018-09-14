#ifndef BUS_H
#define BUS_H

#include <Arduino.h>

template <typename T>
class Bus {
private:
    byte pins[sizeof(T) * 8];
    
    
public:
    Bus(byte pins[sizeof(T) * 8]);
    void set_mode(byte mode);
    void set(T data);
    T get();
    
};

#endif
