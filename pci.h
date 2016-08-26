#ifndef _PCI_H_
#define _PCI_H_ 1

#include "port.h"

/*
 * PCI Device Descriptor
 * Describes port_no,
 * int_no, bus_no and
 * many other descriptors
 * listed below
 */
struct PCI_DESCRIPTOR
{
    uint32_t portBase;
    uint32_t interrupt;

    uint16_t bus;
    uint16_t device;
    uint16_t function;

    uint16_t vendor_id;
    uint16_t device_id;

    uint8_t class_id;
    uint8_t subclass_id;
    uint8_t interface_id;

    uint8_t revision;
};

class PCI_CONTROLLER
{

public:
	PCI_CONTROLLER();
	~PCI_CONTROLLER();
	uint16_t read(uint8_t bus, uint8_t slot,uint8_t func, uint8_t offset);
	void write(uint8_t bus, uint8_t slot,uint8_t func, uint8_t offset,uint32_t value);

	bool deviceHasFunc(uint16_t bus, uint16_t device);
	PCI_DESCRIPTOR GetDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function);

	void printDrivers();
private:
	PORT::Port32Bits commandPort;
	PORT::Port32Bits dataPort;
};

#endif
