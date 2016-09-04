#include "rand.h"

static SerialPort sp;

extern "C" uint8_t randomnumber();

void randomnumberc()
{
	sp.write_number_serial(randomnumber());
}
