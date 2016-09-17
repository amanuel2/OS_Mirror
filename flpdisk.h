#ifndef _FLPDISK_H_
#define _FLPDISK_H_ 1

#include "port.h"
#include "time.h"

extern void flpydsk_install (int irq);

//! set current working drive
extern void flpydsk_set_working_drive (uint8_t drive);

//! get current working drive
extern uint8_t flpydsk_get_working_drive ();

//! read a sector
extern uint8_t* flpydsk_read_sector (int sectorLBA);

//! converts an LBA address to CHS
extern void flpydsk_lba_to_chs (int lba,int *head,int *track,int *sector);

#endif