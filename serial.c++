#include "serial.h"
#define PORT 0x3f8   /* PORT1 */

const uint16_t baud = 300	;
const int divisor = 115200/baud;

SerialPort::SerialPort()
{
    p8b.out(0x00,(uint16_t) PORT + (uint16_t) 1); /* Disable interrupts */
    p8b.out(0x80,(uint16_t) PORT + (uint16_t) 3); /* Enable divisor mode */
	p8b.out(0x03,(uint16_t) PORT + (uint16_t) 0); /* Div Low:  01 Set the port to 115200 bps */
	p8b.out(0x00,(uint16_t) PORT + (uint16_t) 1); /* Div High: 00 */
	p8b.out(0x03,(uint16_t) PORT + (uint16_t) 3); /* Disable divisor mode, set parity */
	p8b.out(0xC7,(uint16_t) PORT + (uint16_t) 2); /* Enable FIFO and clear */
	p8b.out(0x0B,(uint16_t) PORT + (uint16_t) 4); /* Enable interrupts */
//	p8b.out(0x01,PORT a+ 1); /* Enable interrupts */
}


int SerialPort::serial_received() {
   return p8b.in(PORT + 5) & 1;
}

char SerialPort::read_serial() {
   while (serial_received() == 0);

   return p8b.in(PORT);
}

int SerialPort::is_transmit_empty() {
   return p8b.in((uint16_t)(PORT + 5)) & 0x20;
}

void SerialPort::write_serial(char a) {
   while (is_transmit_empty() == 0);

   p8b.out(a,(uint16_t)PORT);
}

void SerialPort::write_string_serial(char* str)
{
	while (is_transmit_empty() == 0);

	for(int32_t i=0; i<strlen((int8_t*)str); i++)
	{
		p8b.out(str[i],(uint16_t)PORT);
	}
}

void SerialPort::write_number_serial(int32_t num)
{
	while (is_transmit_empty() == 0);
	char* str_conv = itoa(num);
	for(int32_t i=0; i<strlen((int8_t*)str_conv); i++)
	{
		p8b.out(str_conv[i],(uint16_t)PORT);
	}
}

SerialPort::~SerialPort()
{}
