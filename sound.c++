#include "sound.h"

static PORT::Port8Bits p8b;

Sound::Sound()
{

}

Sound::~Sound()
{

}

void Sound::beep(uint32_t seconds)
{

        //Set the PIT to the desired frequency
	uint32_t nFrequence = 500;
 	uint32_t Div = 1193180 / nFrequence;
 	p8b.out(0xb6,0x43);
 	p8b.out((uint8_t) (Div),0x42 );
 	p8b.out((uint8_t) (Div >> 8),0x42);
 
        //And play the sound using the PC speaker
 	uint8_t tmp = p8b.in(0x61);
  	if (tmp != (tmp | 3))
 		p8b.out(tmp | 3,0x61);

 	delay(seconds);

 	p8b.out((p8b.in(0x61) & 0xFC),0x61);
}