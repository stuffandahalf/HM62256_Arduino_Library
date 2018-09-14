#include <HM62256.h>

HM62256::HM62256(Bus<hm62256_address_t> *address_bus, Bus<hm62256_data_t> *data_bus, byte read_pin, byte write_pin) {
    this->address_bus = address_bus;
    this->data_bus = data_bus;
    
    this->read_pin = read_pin;
    this->write_pin = write_pin;
    
    pinMode(this->read_pin, OUTPUT);
    pinMode(this->write_pin, OUTPUT);
    
    this->set_mode(HM62256_NOOUT);
}

hm62256_data_t HM62256::read(hm62256_address_t address) {
    hm62256_data_t data;
    this->set_mode(HM62256_READ);
    
    this->address_bus->set(address);
    data = this->data_bus->get();
    
    this->set_mode(HM62256_NOOUT);
    return data;
}

void HM62256::write(hm62256_address_t address, hm62256_data_t data) {
    this->set_mode(HM62256_WRITE);
    
    this->address_bus->set(address);
    this->data_bus->set(data);
    
    this->set_mode(HM62256_NOOUT);
}

void HM62256::set_mode(byte mode) {
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
