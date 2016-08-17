#include "bitset.h"

Bit::Bit(uint32_t max_bit , uint32_t address)
{
	this->bitset.address = address;
	this->bitset.max_bit = max_bit;
}

Bit::Bit()
{

}

Bit::Bit(bitset_t bitset_par)
{
	this->bitset = bitset_par;
}

void Bit::set_adress(uint32_t address)
{
	this->bitset.address = address;
}

void Bit::set_max_bit(uint32_t max_bit)
{
	this->bitset.max_bit = max_bit;
}

void Bit::setbit(int bit_to_set)
{
	this->bitset.address |= 1 << bit_to_set;
}

void Bit::clearbit(int bit_to_clear)
{
	this->bitset.address &= ~(1<<bit_to_clear);
}

uint32_t Bit::checkbit(int bit_to_check)
{
	return ((this->bitset.address>>bit_to_check)&1);
}


Bit::~Bit()
{

}
