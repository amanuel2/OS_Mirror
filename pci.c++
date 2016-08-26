#include "pci.h"

extern void printf(char *str, ...);

PCI_CONTROLLER::PCI_CONTROLLER(void)
{

}

PCI_CONTROLLER::~PCI_CONTROLLER(void)
{

}


uint16_t PCI_CONTROLLER::read(uint8_t bus, uint8_t slot,uint8_t func, uint8_t offset)
{
		uint32_t address;
	    uint32_t lbus  = (uint32_t)bus;
	    uint32_t lslot = (uint32_t)slot;
	    uint32_t lfunc = (uint32_t)func;
	    uint16_t tmp = 0;

	    /* create configuration address as per Figure 1 */
	    address = (uint32_t)((lbus << 16)
	    		   |(lslot << 11)
				   |(lfunc << 8)
				   |(offset & 0xfc)
				   |((uint32_t)0x80000000));

	    /* write out the address */
	    commandPort.out(address,0xCF8);
	    /* this->read in the data */
	    /* (offset & 2) * 8) = 0 will choose the first word of the 32 bits register */
	    tmp = (uint16_t)((dataPort.in(0xCFC) >> ((offset & 2) * 8)) & 0xffff);
	    return (tmp);
}

void PCI_CONTROLLER::write(uint8_t bus, uint8_t slot,uint8_t func, uint8_t offset,uint32_t value)
{

	uint32_t id =
	        0x1 << 31
	        | ((bus & 0xFF) << 16)
	        | ((slot & 0x1F) << 11)
	        | ((func & 0x07) << 8)
	        | (offset & 0xFC);
	commandPort.out(id,0xCF8);
	dataPort.out(value,0xCFC);

}

bool PCI_CONTROLLER::deviceHasFunc(uint16_t bus, uint16_t device)
{
    return this->read(bus, device, 0, 0x0E) & (1<<7);
}

PCI_DESCRIPTOR PCI_CONTROLLER::GetDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function)
{
	  	PCI_DESCRIPTOR result;

	    result.bus = bus;
	    result.device = device;
	    result.function = function;

	    result.vendor_id = this->read(bus, device, function, 0x00);
	    result.device_id = this->read(bus, device, function, 0x02);

	    result.class_id = this->read(bus, device, function, 0x0b);
	    result.subclass_id = this->read(bus, device, function, 0x0a);
	    result.interface_id = this->read(bus, device, function, 0x09);

	    result.revision = this->read(bus, device, function, 0x08);
	    result.interrupt = this->read(bus, device, function, 0x3c);

	    return result;
}

void PCI_CONTROLLER::printDrivers()
{
	printf("********PCI*********\n");
	  for(int bus = 0; bus < 8; bus++)
	    {
	        for(int device = 0; device < 32; device++)
	        {
	            int numFunctions = deviceHasFunc(bus, device) ? 8 : 1;
	            for(int function = 0; function < numFunctions; function++)
	            {
	                PCI_DESCRIPTOR dev = GetDeviceDescriptor(bus, device, function);

	                if(dev.vendor_id == 0x0000 || dev.vendor_id == 0xFFFF)
	                    break;

	                printf("PCI BUS ");
	                printf("%x",bus & 0xFF);

	                printf(", DEVICE ");
	                printf("%x",device & 0xFF);

	                printf(", FUNCTION ");
	                printf("%x", function & 0xFF);

	                printf(" , VENDOR ");
	                uint32_t vendor_id = (dev.vendor_id & 0xFF00) | (dev.vendor_id & 0xFF);
	                if(vendor_id == 0x8086)
	                	printf("INTEL");
	                else if(vendor_id == 0x80EE)
	                	printf("Oracle");
	                else if(vendor_id == 0x1002 || vendor_id == 1022)
	                	printf("AMD");
	                else
	                	printf("0x%x",vendor_id);

	                printf(", DEVICE ");
	                printf("%x",(dev.device_id & 0xFF00) >> 8);
	                printf("%x",dev.device_id & 0xFF);
	                printf("\n");
	            }
	        }
	    }
	printf("********************");
}
