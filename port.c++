#include "port.h"


extern "C" uint8_t inport8(uint16_t port_number);
extern "C" void outport8(uint16_t port_number,uint8_t data);
extern "C" uint16_t inport16(uint16_t port_number);
extern "C" void outport16(uint16_t port_number,uint16_t data);
extern "C" uint32_t inport32(uint16_t port_number);
extern "C" void outport32(uint16_t port_number,uint32_t data);

PORT::Port::Port()
{}
PORT::Port::~Port(){};


//8BITS
PORT::Port8Bits::Port8Bits()
{}

PORT::Port8Bits::~Port8Bits(){};
uint8_t PORT::Port8Bits::Port8Bits::in(uint16_t port_number_param)
{
     return inport8(port_number_param);
}
 void PORT::Port8Bits::out(uint8_t data,uint16_t port_number_param)
{
    outport8(port_number_param,data);
}

//16BITS

PORT::Port16Bits::Port16Bits()
{}
PORT::Port16Bits::~Port16Bits(){};


uint16_t PORT::Port16Bits::in(uint16_t port_number_param)
{
     return inport16(port_number_param);
}
void PORT::Port16Bits::out(uint16_t data,uint16_t port_number_param)
{
    return outport16(port_number_param,data);
}


//32BITS

PORT::Port32Bits::Port32Bits()
{}
PORT::Port32Bits::~Port32Bits(){};
uint32_t PORT::Port32Bits::in(uint16_t port_number_param)
{
     return inport32(port_number_param);
}
 void PORT::Port32Bits::out(uint32_t data,uint16_t port_number_param)
{
	 outport32(port_number_param,data);
}
