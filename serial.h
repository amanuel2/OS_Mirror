#ifndef _SERIAL_H_
#define _SERIAL_H_ 1

#include <stdint.h>
#include "port.h"
#include "stdio.h"

class SerialPort
{
public:
	SerialPort();
	~SerialPort();
	char read_serial();
	void write_serial(char a);
	void write_string_serial(char* str);
	void write_number_serial(int32_t num);
	void write_hex_serial(uint8_t num);
private:
	PORT::Port8Bits p8b;
	int serial_received();
	int is_transmit_empty();
};

#endif
