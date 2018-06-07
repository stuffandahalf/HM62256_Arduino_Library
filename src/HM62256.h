/*
 * HM62256.h - Library for interfacing with Hitachi SRAM chips.
 * Created by Gregory Norton. May 20, 2018
 */

#ifndef HM62256_H
#define HM62256_H

#include <Arduino.h>

#define HM62256_ADDRESS_WIDTH 16
#define HM62256_DATA_WIDTH 8

#define HM62256_MEMORY_SIZE 32768

#define HM62256_READ 0
#define HM62256_WRITE 1
#define HM62256_NOOUT 2

typedef uint16_t address;

class HM62256 {
    private:
        byte read_pin;
        byte write_pin;

        byte *data_bus;
        byte *address_bus;
        //uint16_t memory_size;

        void setDataBusMode(byte mode);
        void setAddressBusMode(byte mode);
        void setAddress(address addr);
        void setMode(byte mode);
        //void detect();

    public:
        //HM62256();
        HM62256(byte *address_bus_pins, byte *data_bus_pins, byte read_pin, byte write_pin);
        ~HM62256();
        byte get(address addr);
        void set(address addr, byte data);
        void clear();
};

#endif
