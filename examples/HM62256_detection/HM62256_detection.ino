#include <HM62256.h>

HM62256 *mem;

void setup() {
    Serial.begin(115200);
    
    byte address_bus_pins[sizeof(hm62256_address_t) * 8];
    for (size_t i = 0; i < sizeof(hm62256_address_t) * 8; i++) {
        address_bus_pins[i] = 53 - 2 * i;
    }
    
    byte data_bus_pins[sizeof(hm62256_data_t) * 8];
    for (size_t i = 0; i < sizeof(hm62256_data_t) * 8; i++) {
        data_bus_pins[i] = 52 - 2 * i;
    }
    
    byte read_pin = 24;
    byte write_pin = 22;
    
    pinMode(read_pin, OUTPUT);
    pinMode(write_pin, OUTPUT);
    
    Bus<hm62256_address_t> *address_bus = new Bus<hm62256_address_t>(address_bus_pins);
    Bus<hm62256_data_t> *data_bus = new Bus<hm62256_data_t>(data_bus_pins);
    
    mem = new HM62256(address_bus, data_bus, read_pin, write_pin);
    
    hm62256_address_t size = 0;
    for (hm62256_address_t i = 0; i < 0xFFFF; i++) {
        mem->write(i, i & 0xFF);
        /*Serial.print(i, HEX);
        Serial.print(":\t");
        Serial.println(mem->read(i), HEX);*/
        if (mem->read(i) != (i & 0xFF)) {
            break;
        }
        size++;
    }
    
    Serial.print("Detected ");
    Serial.print(size);
    Serial.println(" bytes");
    
    Serial.println("Done");
    
    free(mem);
    free(data_bus);
    free(address_bus);
}

void loop() {
    
}
