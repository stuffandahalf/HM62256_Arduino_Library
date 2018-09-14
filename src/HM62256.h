/*
 * HM62256.h - Library for interfacing with Hitachi SRAM chips.
 * Created by Gregory Norton. May 20, 2018
 */

#ifndef HM62256_H
#define HM62256_H

#include <Arduino.h>
#include "Bus.h"

#define HM62256_NOOUT 0
#define HM62256_READ 1
#define HM62256_WRITE 2

typedef uint16_t hm62256_address_t;
typedef uint8_t hm62256_data_t;

class HM62256 {
private:
    Bus<hm62256_data_t> *data_bus;
    Bus<hm62256_address_t> *address_bus;
    byte read_pin;
    byte write_pin;
    
    void set_mode(byte mode);
    
public:
    HM62256(Bus<hm62256_address_t> *address_bus, Bus<hm62256_data_t> *data_bus, byte read_pin, byte write_pin);
    ~HM62256();
    
    hm62256_data_t read(hm62256_address_t address);
    void write(hm62256_address_t address, hm62256_data_t data); 
};

#endif
