#include <HM62256.h>

HM62256 *mem;

void setup() {
    Serial.begin(115200);
    
    byte address_bus_pins[HM62256_MEMORY_WIDTH];
    for (size_t i = 0; i < HM62256_MEMORY_WIDTH; i++) {
        address_bus_pins[i] = 23 + 2 * i;
    }
    
    byte data_bus_pins[HM62256_DATA_WIDTH];
    for (size_t i = 0; i < HM62256_DATA_WIDTH; i++) {
        data_bus_pins[i] = 22 + 2 * i;
    }
    
    byte read_pin = 50;
    byte write_pin = 52;
    
    
    mem = new HM62256(address_bus_pins, data_bus_pins, read_pin, write_pin);
    
    //mem->set(MEMORY_SIZE - 1, 0xFF);
    mem->set(0x0, 0x12);
    //mem->set(MEMORY_SIZE, 0xDF);
    mem->set(mem->size(), 0xDF);
    Serial.println(mem->get(0x0), HEX);
    Serial.println(mem->get(mem->size()), HEX);
    
}

void loop() {
    
}
