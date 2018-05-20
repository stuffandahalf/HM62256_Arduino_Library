#include "HM62256.h"

HM62256::HM62256(byte *address_bus_pins, byte *data_bus_pins, byte read_pin, byte write_pin) {
    this->read_pin = read_pin;
    this->write_pin = write_pin;
    pinMode(this->read_pin, OUTPUT);
    pinMode(this->write_pin, OUTPUT);
    
    this->setMode(HM62256_NOOUT);
    
    this->data_bus = new byte[HM62256_DATA_WIDTH];
    this->memory_bus = new byte[HM62256_MEMORY_WIDTH];
    this->memory_size = 0;
    
    for (int i = 0; i < HM62256_DATA_WIDTH; i++) {
        this->data_bus[i] = data_bus_pins[i];
    }
    
    for (int i = 0; i < HM62256_MEMORY_WIDTH; i++) {
        this->memory_bus[i] = address_bus_pins[i];
        pinMode(this->memory_bus[i], OUTPUT);
    }
    
    //this->detect();
    this->memory_size = HM62256_MEMORY_SIZE;
}

byte HM62256::get(address addr) {
    this->setDataBusMode(INPUT_PULLUP);
    this->setAddress(addr);
    this->setMode(HM62256_READ);
    byte data = 0;
    
    for (int i = HM62256_DATA_WIDTH - 1; i >= 0; i--) {
        data += digitalRead(this->data_bus[i]);
        if (i) {
            data <<= 1;
        }
    }
    
    this->setMode(HM62256_NOOUT);
    
    return data;
}

void HM62256::set(address addr, byte data) {
    this->setDataBusMode(OUTPUT);
    this->setAddress(addr);
    this->setMode(HM62256_WRITE);
    
    for (int i = 0; i < HM62256_DATA_WIDTH; i++) {
        digitalWrite(this->data_bus[i], data & 1);
        data >>= 1;
    }
    
    this->setMode(HM62256_NOOUT);
}

void HM62256::detect() {
    Serial.println("Detecting available RAM");
    bool complete = false;
    while (!complete && (this->memory_size < UINT16_MAX)) {
        Serial.println(this->memory_size);
        for (uint8_t i = 0; i < UINT8_MAX; i++) {
            //Serial.println(i, HEX);
            this->set(this->memory_size, i);
            if (this->get(this->memory_size) != i) {
                //Serial.println(i);
                complete = true;
                break;
            }
            //delay(10);
        }
        if (!complete) {
            this->memory_size++;
        }
    }
    
    Serial.print("Detected ");
    Serial.print(this->memory_size);
    Serial.println(" bytes");
}

void HM62256::clear() {
    Serial.println("Memory will be cleared");
    for(address i = 0; i < this->memory_size; i++) {
        //Serial.println(i, HEX);
        this->set(i, 0);
    }
    Serial.println("Memory has been cleared");
}

void HM62256::setDataBusMode(byte mode) {
    for (int i = 0; i < HM62256_DATA_WIDTH; i++) {
        pinMode(this->data_bus[i], mode);
    }
}

void HM62256::setAddress(address addr) {
    for (int i = 0; i < HM62256_MEMORY_WIDTH; i++) {
        digitalWrite(this->memory_bus[i], addr & 1);
        addr >>= 1;
    }
}

void HM62256::setMode(byte mode) {
    if (mode == HM62256_READ) {
        digitalWrite(this->read_pin, LOW);
        digitalWrite(this->write_pin, HIGH);
    }
    else if (mode == HM62256_WRITE) {
        digitalWrite(this->read_pin, HIGH);
        digitalWrite(this->write_pin, LOW);
    }
    else if (mode == HM62256_NOOUT) {
        digitalWrite(this->read_pin, HIGH);
        digitalWrite(this->write_pin, HIGH);
    }
}

address HM62256::size() {
    return this->memory_size;
}

HM62256::~HM62256() {
    delete(this->data_bus);
    delete(this->memory_bus);
}
