#ifndef _BEEP_H_
#define _BEEP_H_ 1

#include "port.h"
#include "time.h"

static PORT::Port8Bits p8b;

 //Play sound using built in speaker
 extern "C" void play_sound(uint32_t nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;
 
        //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	p8b.out(0xb6,0x43);
 	p8b.out((uint8_t) (Div),0x42 );
 	p8b.out((uint8_t) (Div >> 8),0x42);
 
        //And play the sound using the PC speaker
 	tmp = p8b.in(0x61);
  	if (tmp != (tmp | 3)) {
 		p8b.out(tmp | 3,0x61);
 	}
 }
 
 //make it shutup
 extern "C" void nosound() {
 	uint8_t tmp = p8b.in(0x61) & 0xFC;
 
 	p8b.out(tmp,0x61);
 }
 
 //Make a beep
 extern "C" void beep() {
 	printf("Here");
 	 play_sound(1000);
 	  delay(5);
 	  nosound();
 	 printf("End");
 }

#endif