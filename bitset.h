#ifndef _BITSET_H_
#define _BITSET_H_ 1

#include <stdint.h>


typedef struct
{
	uint32_t max_bit;
	uint32_t address;
}bitset_t;


class Bit
{
public:
	Bit(uint32_t max_bit , uint32_t adress);
	Bit(bitset_t bitset_par);
	Bit();
	void setbit(int bit_to_set);
	void set_adress(uint32_t address);
	void set_max_bit(uint32_t max_bit);
	void clearbit(int bit_to_clear);
	uint32_t checkbit(int bit_to_check);
	~Bit();
private:
	bitset_t bitset;
};

#endif
