#include "flpdisk.h"

typedef void(*regs_func)(struct regs *r);

extern void install_handler_irq(int irq, regs_func handler);

static PORT::Port8Bits p8b;

enum FLPYDSK_IO {

	FLPYDSK_DOR		=	0x3f2,
	FLPYDSK_MSR		=	0x3f4,
	FLPYDSK_FIFO	=	0x3f5,
	FLPYDSK_CTRL	=	0x3f7
};

/**
*	Bits 0-4 of command byte. Please see chapter for additional commands
*/

enum FLPYDSK_CMD {

	FDC_CMD_READ_TRACK	=	2,
	FDC_CMD_SPECIFY		=	3,
	FDC_CMD_CHECK_STAT	=	4,
	FDC_CMD_WRITE_SECT	=	5,
	FDC_CMD_READ_SECT	=	6,
	FDC_CMD_CALIBRATE	=	7,
	FDC_CMD_CHECK_INT	=	8,
	FDC_CMD_FORMAT_TRACK=	0xd,
	FDC_CMD_SEEK		=	0xf
};

/**
*	Additional command masks. Can be masked with above commands
*/

enum FLPYDSK_CMD_EXT {

	FDC_CMD_EXT_SKIP		=	0x20,	//00100000
	FDC_CMD_EXT_DENSITY		=	0x40,	//01000000
	FDC_CMD_EXT_MULTITRACK	=	0x80	//10000000
};

/*
**	Digital Output Register
*/

enum FLPYDSK_DOR_MASK {

	FLPYDSK_DOR_MASK_DRIVE0			=	0,	//00000000	= here for completeness sake
	FLPYDSK_DOR_MASK_DRIVE1			=	1,	//00000001
	FLPYDSK_DOR_MASK_DRIVE2			=	2,	//00000010
	FLPYDSK_DOR_MASK_DRIVE3			=	3,	//00000011
	FLPYDSK_DOR_MASK_RESET			=	4,	//00000100
	FLPYDSK_DOR_MASK_DMA			=	8,	//00001000
	FLPYDSK_DOR_MASK_DRIVE0_MOTOR	=	16,	//00010000
	FLPYDSK_DOR_MASK_DRIVE1_MOTOR	=	32,	//00100000
	FLPYDSK_DOR_MASK_DRIVE2_MOTOR	=	64,	//01000000
	FLPYDSK_DOR_MASK_DRIVE3_MOTOR	=	128	//10000000
};

/**
*	Main Status Register
*/

enum FLPYDSK_MSR_MASK {

	FLPYDSK_MSR_MASK_DRIVE1_POS_MODE	=	1,	//00000001
	FLPYDSK_MSR_MASK_DRIVE2_POS_MODE	=	2,	//00000010
	FLPYDSK_MSR_MASK_DRIVE3_POS_MODE	=	4,	//00000100
	FLPYDSK_MSR_MASK_DRIVE4_POS_MODE	=	8,	//00001000
	FLPYDSK_MSR_MASK_BUSY				=	16,	//00010000
	FLPYDSK_MSR_MASK_DMA				=	32,	//00100000
	FLPYDSK_MSR_MASK_DATAIO				=	64, //01000000
	FLPYDSK_MSR_MASK_DATAREG			=	128	//10000000
};

/**
*	Controller Status Port 0
*/

enum FLPYDSK_ST0_MASK {

	FLPYDSK_ST0_MASK_DRIVE0		=	0,		//00000000	=	for completness sake
	FLPYDSK_ST0_MASK_DRIVE1		=	1,		//00000001
	FLPYDSK_ST0_MASK_DRIVE2		=	2,		//00000010
	FLPYDSK_ST0_MASK_DRIVE3		=	3,		//00000011
	FLPYDSK_ST0_MASK_HEADACTIVE	=	4,		//00000100
	FLPYDSK_ST0_MASK_NOTREADY	=	8,		//00001000
	FLPYDSK_ST0_MASK_UNITCHECK	=	16,		//00010000
	FLPYDSK_ST0_MASK_SEEKEND	=	32,		//00100000
	FLPYDSK_ST0_MASK_INTCODE	=	64		//11000000
};

/*
** LPYDSK_ST0_MASK_INTCODE types
*/

enum FLPYDSK_ST0_INTCODE_TYP {

	FLPYDSK_ST0_TYP_NORMAL		=	0,
	FLPYDSK_ST0_TYP_ABNORMAL_ERR=	1,
	FLPYDSK_ST0_TYP_INVALID_ERR	=	2,
	FLPYDSK_ST0_TYP_NOTREADY	=	3
};

/**
*	GAP 3 sizes
*/

enum FLPYDSK_GAP3_LENGTH {

	FLPYDSK_GAP3_LENGTH_STD = 42,
	FLPYDSK_GAP3_LENGTH_5_14= 32,
	FLPYDSK_GAP3_LENGTH_3_5= 27
};

/*
**	Formula: 2^sector_number * 128, where ^ denotes "to the power of"
*/

enum FLPYDSK_SECTOR_DTL {

	FLPYDSK_SECTOR_DTL_128	=	0,
	FLPYDSK_SECTOR_DTL_256	=	1,
	FLPYDSK_SECTOR_DTL_512	=	2,
	FLPYDSK_SECTOR_DTL_1024	=	4
};

//! floppy irq
const int FLOPPY_IRQ = 6;

//! sectors per track
const int FLPY_SECTORS_PER_TRACK = 18;

//! dma tranfer buffer starts here and ends at 0x1000+64k
//! You can change this as needed. It must be below 16MB and in idenitity mapped memory!
const int DMA_BUFFER = 0x1000;

//============================================================================
//    IMPLEMENTATION PRIVATE CLASS PROTOTYPES / EXTERNAL CLASS REFERENCES
//============================================================================
//============================================================================
//    IMPLEMENTATION PRIVATE STRUCTURES / UTILITY CLASSES
//============================================================================
//============================================================================
//    IMPLEMENTATION REQUIRED EXTERNAL REFERENCES (AVOID)
//============================================================================

//! used to wait in miliseconds
extern void sleep(uint32_t seconds);
//============================================================================

//! initialize DMA to use phys addr 84k-128k
void flpydsk_initialize_dma () {

	p8b.out (0x06,0x0a);	//mask dma channel 2
	p8b.out (0xff,0xd8);	//reset master flip-flop
	p8b.out ( 0,0x04);     //address=0x1000 
	p8b.out ( 0x10,0x04);
	p8b.out ( 0xff,0xd8);  //reset master flip-flop
	p8b.out ( 0xff,0x05);  //count to 0x23ff (number of bytes in a 3.5" floppy disk track)
	p8b.out ( 0x23,0x05);
	p8b.out ( 0,0x80);     //external page register = 0
	p8b.out ( 0x02,0x0a);  //unmask dma channel 2
}

//! prepare the DMA for read transfer
void flpydsk_dma_read () {

	p8b.out (0x06,0x0a); //mask dma channel 2
	p8b.out (0x56,0x0b); //single transfer, address increment, autoinit, read, channel 2
	p8b.out (0x02,0x0a); //unmask dma channel 2
}

//! prepare the DMA for write transfer
void flpydsk_dma_write () {

	p8b.out (0x06,0x0a); //mask dma channel 2
	p8b.out (0x5a,0x0b); //single transfer, address increment, autoinit, write, channel 2
	p8b.out (0x02,0x0a); //unmask dma channel 2
}

uint8_t flpydsk_read_status () {

	//! just return main status register
	return p8b.in(FLPYDSK_MSR);
}

//! write to the fdc dor
void flpydsk_write_dor (uint8_t val ) {

	//! write the digital output register
	p8b.out( val,FLPYDSK_DOR);
}

//! send command byte to fdc
void flpydsk_send_command (uint8_t cmd) {

	//! wait until data register is ready. We send commands to the data register
	for (int i = 0; i < 500; i++ )
		if ( flpydsk_read_status () & FLPYDSK_MSR_MASK_DATAREG )
			return p8b.out( cmd,FLPYDSK_FIFO);
}

//! get data from fdc
uint8_t flpydsk_read_data () {

	//! same as above function but returns data register for reading
	for (int i = 0; i < 500; i++ )
		if ( flpydsk_read_status () & FLPYDSK_MSR_MASK_DATAREG )
			return p8b.in(FLPYDSK_FIFO);

	return 0;
}

//! write to the configuation control register
void flpydsk_write_ccr (uint8_t val) {

	//! write the configuation control
	p8b.out( val,FLPYDSK_CTRL);
}

/**
*	Interrupt Handling Routines
*/
static volatile uint8_t _FloppyDiskIRQ = 0;
//! wait for irq to fire
inline void flpydsk_wait_irq () {

	//! wait for irq to fire
	while ( _FloppyDiskIRQ == 0)
		;
	_FloppyDiskIRQ = 0;
}

//!	floppy disk irq handler
void  i86_flpy_irq (struct regs *r) {
	//! irq fired
	_FloppyDiskIRQ = 1;
}
//! check interrupt status command
void flpydsk_check_int (uint32_t* st0, uint32_t* cyl) {

	flpydsk_send_command (FDC_CMD_CHECK_INT);

	*st0 = flpydsk_read_data ();
	*cyl = flpydsk_read_data ();
}


uint8_t	_CurrentDrive = 0;
//! turns the current floppy drives motor on/off
void flpydsk_control_motor (bool b) {

	//! sanity check: invalid drive
	if (_CurrentDrive > 3)
		return;

	uint32_t motor = 0;

	//! select the correct mask based on current drive
	switch (_CurrentDrive) {

		case 0:
			motor = FLPYDSK_DOR_MASK_DRIVE0_MOTOR;
			break;
		case 1:
			motor = FLPYDSK_DOR_MASK_DRIVE1_MOTOR;
			break;
		case 2:
			motor = FLPYDSK_DOR_MASK_DRIVE2_MOTOR;
			break;
		case 3:
			motor = FLPYDSK_DOR_MASK_DRIVE3_MOTOR;
			break;
	}

	//! turn on or off the motor of that drive
	if (b)
		flpydsk_write_dor (_CurrentDrive | motor | FLPYDSK_DOR_MASK_RESET | FLPYDSK_DOR_MASK_DMA);
	else
		flpydsk_write_dor (FLPYDSK_DOR_MASK_RESET);

	//! in all cases; wait a little bit for the motor to spin up/turn off
	//sleep (1);
}

//! configure drive
void flpydsk_drive_data (uint32_t stepr, uint32_t loadt, uint32_t unloadt, bool dma ) {

	uint32_t data = 0;

	//! send command
	flpydsk_send_command (FDC_CMD_SPECIFY);
	data = ( (stepr & 0xf) << 4) | (unloadt & 0xf);
		flpydsk_send_command (data);
	data = (loadt) << 1 | (dma==false) ? 0 : 1;
		flpydsk_send_command (data);
}

//! calibrates the drive
int flpydsk_calibrate (uint32_t drive) {

	uint32_t st0, cyl;

	if (drive >= 4)
		return -2;
printf("TURNING MOTOR ON");
	//! turn on the motor
	flpydsk_control_motor (true); 
printf("FLPDISK MOTOR ON");
	for (int i = 0; i < 10; i++) {
		printf("ITTERATE %d",i);
		//! send command
		flpydsk_send_command ( FDC_CMD_CALIBRATE );
		flpydsk_send_command ( drive );
		flpydsk_wait_irq ();
		flpydsk_check_int ( &st0, &cyl);

		//! did we fine cylinder 0? if so, we are done
		if (!cyl) {

			flpydsk_control_motor (false);
			return 0;
		}
	}

	flpydsk_control_motor (false);
	return -1;
}

//! disable controller
void flpydsk_disable_controller () {

	flpydsk_write_dor (0);
}

//! enable controller
void flpydsk_enable_controller () {

	flpydsk_write_dor ( FLPYDSK_DOR_MASK_RESET | FLPYDSK_DOR_MASK_DMA);
}

//! reset controller
void flpydsk_reset () {

	uint32_t st0, cyl;
	_FloppyDiskIRQ = 0;
	//! reset the controller
	flpydsk_disable_controller ();
	flpydsk_enable_controller ();
	//flpydsk_wait_irq ();
	while(_FloppyDiskIRQ == 0);
		_FloppyDiskIRQ = 0;



	//! send CHECK_INT/SENSE INTERRUPT command to all drives
	for (int i=0; i<4; i++)
		flpydsk_check_int (&st0,&cyl);


	//! transfer speed 500kb/s
	flpydsk_write_ccr (0);

	//! pass mechanical drive info. steprate=3ms, unload time=240ms, load time=16ms
	flpydsk_drive_data (3,16,240,true);


	//! calibrate the disk
	flpydsk_calibrate ( _CurrentDrive );


	printf("End Wait");

}

//! read a sector
void flpydsk_read_sector_imp (uint8_t head, uint8_t track, uint8_t sector) {

	uint32_t st0, cyl;

	//! set the DMA for read transfer
	flpydsk_dma_read ();

	//! read in a sector
	flpydsk_send_command (
				FDC_CMD_READ_SECT | FDC_CMD_EXT_MULTITRACK | FDC_CMD_EXT_SKIP | FDC_CMD_EXT_DENSITY);
	flpydsk_send_command ( head << 2 | _CurrentDrive );
	flpydsk_send_command ( track);
	flpydsk_send_command ( head);
	flpydsk_send_command ( sector);
	flpydsk_send_command ( FLPYDSK_SECTOR_DTL_512 );
	flpydsk_send_command ( ( ( sector + 1 ) >= FLPY_SECTORS_PER_TRACK ) ? FLPY_SECTORS_PER_TRACK : sector + 1 );
	flpydsk_send_command ( FLPYDSK_GAP3_LENGTH_3_5 );
	flpydsk_send_command ( 0xff );

	//! wait for irq
	flpydsk_wait_irq ();

	//! read status info
	for (int j=0; j<7; j++)
		flpydsk_read_data ();

	//! let FDC know we handled interrupt
	flpydsk_check_int (&st0,&cyl);
}

//! seek to given track/cylinder
int flpydsk_seek ( uint32_t cyl, uint32_t head ) {

	uint32_t st0, cyl0;

	if (_CurrentDrive >= 4)
		return -1;

	for (int i = 0; i < 10; i++ ) {

		//! send the command
		flpydsk_send_command (FDC_CMD_SEEK);
		flpydsk_send_command ( (head) << 2 | _CurrentDrive);
		flpydsk_send_command (cyl);

		//! wait for the results phase IRQ
		flpydsk_wait_irq ();
		flpydsk_check_int (&st0,&cyl0);

		//! found the cylinder?
		if ( cyl0 == cyl)
			return 0;
	}

	return -1;
}

//============================================================================
//    INTERFACE FUNCTIONS
//============================================================================

//! convert LBA to CHS
void flpydsk_lba_to_chs (int lba,int *head,int *track,int *sector) {

   *head = ( lba % ( FLPY_SECTORS_PER_TRACK * 2 ) ) / ( FLPY_SECTORS_PER_TRACK );
   *track = lba / ( FLPY_SECTORS_PER_TRACK * 2 );
   *sector = lba % FLPY_SECTORS_PER_TRACK + 1;
}

//! install floppy driver
void flpydsk_install (int irq) {
	//! install irq handler
	install_handler_irq (irq, i86_flpy_irq);

	//! initialize the DMA for FDC
	flpydsk_initialize_dma ();
printf("FLP_START");
	//! reset the fdc
	flpydsk_reset ();
printf("FLPDISK_END_RESET");
	//! set drive information
	flpydsk_drive_data (13, 1, 0xf, true);
	printf("FLPDISK_END");
}

//! set current working drive
void flpydsk_set_working_drive (uint8_t drive) {

	if (drive < 4)
		_CurrentDrive = drive;
}

//! get current working drive
uint8_t flpydsk_get_working_drive () {

	return _CurrentDrive;
}

//! read a sector
uint8_t* flpydsk_read_sector (int sectorLBA) {

	if (_CurrentDrive >= 4)
		return 0;

	//! convert LBA sector to CHS
	int head=0, track=0, sector=1;
	flpydsk_lba_to_chs (sectorLBA, &head, &track, &sector);

	//! turn motor on and seek to track
	flpydsk_control_motor (true);
	if (flpydsk_seek (track, head) != 0)
		return 0;

	//! read sector and turn motor off
	flpydsk_read_sector_imp (head, track, sector);
	flpydsk_control_motor (false);

	//! warning: this is a bit hackish
	return (uint8_t*) DMA_BUFFER;
}
