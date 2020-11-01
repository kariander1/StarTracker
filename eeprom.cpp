// 
// 
// 

#include "eeprom.h"

short EepromClass::readShort(const unsigned short &address)
{
	const unsigned short stored_value = (eeprom_read_byte((const uint8_t*)address)<<8) + eeprom_read_byte((const uint8_t*)(address+1));
	//Serial.print("Read a value of ");
	//Serial.println(stored_value);
	return stored_value;

}
void EepromClass::writeShort(const unsigned short &address ,const unsigned short &value)
{
	const  uint8_t lsb = (const uint8_t)(value & 0x0FF);
	const  uint8_t msb = (const uint8_t)((value & 0xF00)>>8);
	/*
	Serial.print("Got value of ");
	Serial.print(value);
	Serial.print(", LSB is ");
	Serial.print(lsb);
	Serial.print(", MSB is ");
	Serial.println(msb);
	*/
	eeprom_write_byte((uint8_t*)(address), msb);
	eeprom_write_byte((uint8_t*)(address+1), lsb);
}




