#include <HM62256.h>

/* For this example, connect the highest
 * address bit to a not gate, and the output to the chip enable pin
 */

HM62256 *mem;

void setup() {
    Serial.begin(115200);
    
    byte address_bus[HM62256_ADDRESS_WIDTH];
    byte data_bus[HM62256_DATA_WIDTH];
    for (size_t i = 0; i < HM62256_ADDRESS_WIDTH; i++) {
        address_bus[i] = 23 + (2 * i);
    }
    for (size_t i = 0; i < HM62256_DATA_WIDTH; i++) {
        data_bus[i] = 22 + 2 * i;
    }
    
    mem = new HM62256(address_bus, data_bus, 50, 52);
    
    mem->set(0x0000, 0xFD);
    mem->set(HM62256_MEMORY_SIZE + 1, 0xFC);
    
    Serial.println(mem->get(0x0000), HEX);
    Serial.println(mem->get(HM62256_MEMORY_SIZE + 1), HEX);
    
    //mem->set(0xFFFE, 0xFD);
    //Serial.println(mem->get(0xFFFE), HEX);
}

void loop() {

}
