#ifndef _PORT_H_
#define _PORT_H_ 1
#include <stdint.h>
namespace PORT
{
	class Port
	{
		protected:
				Port();
				~Port();
	};

	class Port8Bits : public Port
	{
		public:

				Port8Bits();
				~Port8Bits();
				uint8_t in(uint16_t port_number_param);
				void out(uint8_t data,uint16_t port_number_param);
	};

	class Port16Bits : public Port
	{
		public:

				Port16Bits();
				~Port16Bits();
				uint16_t in(uint16_t port_number_param);
				void out(uint16_t data,uint16_t port_number_param);
	};

	class Port32Bits : public Port
	{
		public:

				Port32Bits();
				~Port32Bits();
				uint32_t in(uint16_t port_number_param);
				void out(uint32_t data,uint16_t port_number_param);
	};
};

#endif
