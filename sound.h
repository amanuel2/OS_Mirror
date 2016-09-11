#ifndef _SOUND_H_
#define _SOUND_H_ 1

#include "port.h"
#include "time.h"


class Sound
{
public:
	Sound();
	~Sound();
	/*
		@function beep
			PC Speaker Beep for traditonal error
			Signals. Must have a PC Speaker
			VirtualBox dosent have a PC Speaker,
			Nor Qemu. VMWare does indeed have one,
			as well as your PC
	*/
	void beep(uint32_t seconds);
};

#endif