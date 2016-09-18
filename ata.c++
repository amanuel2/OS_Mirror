#include "ata.h"

static PORT::Port8Bits p8b;
static PORT::Port16Bits p16b;

static const uint32_t bytes_per_sector = 512;


AdvancedTechnologyAttachment::AdvancedTechnologyAttachment(uint16_t portBase,ata_type type)
{
	this->type = type;	
	this->port_def = portBase;
}
AdvancedTechnologyAttachment::~AdvancedTechnologyAttachment()
{

}

void AdvancedTechnologyAttachment::Identify()
{
//Identify What 
	//Drive You want to comunicate with
	//MASTER || SLAVE
	if(this->type == MASTER)
 		p8b.out(0xA0,port_def + 0x6);
	else
		p8b.out(0xB0,port_def + 0x6);

	//Set Bit. Not important
   // p8b.out(0,port_def + 0x206);

    //Begins to talk with master to get status
    p8b.out(0xA0,port_def + 0x6);
    uint8_t status = p8b.in(port_def + 0x7);
    //No device on Bus if
    if(status == 0xFF)
    {
    	this->accesible = false;
        return;
    }
    
    
    if(this->type == MASTER)
 		p8b.out(0xA0,port_def + 0x6);
	else
		p8b.out(0xB0,port_def + 0x6);

	p8b.out(0,port_def + 0x2);
	p8b.out(0,port_def + 0x3);
	p8b.out(0,port_def + 0x4);
	p8b.out(0,port_def + 0x5);
	p8b.out(0xEC,port_def + 0x7); //Identify COMMAND

    
    //get status
    status = p8b.in(port_def + 0x7);
    //No Device on BUS
    if(status == 0x00)
    {
    	this->accesible = false;
        return;
    }
    
    //Wait Until Hard Drive
    //Gets Device anwser to IDENTIFY COMMAND
    while(((status & 0x80) == 0x80)
       && ((status & 0x01) != 0x01))
        status = p8b.in(port_def + 0x7);
     //No Device on Bus   
    if(status & 0x01)
    {
    	this->accesible = false;
        return;
    }
    
    //Finaly read data and print it
    for(int i = 0; i < 256; i++)
    {
        uint16_t data = p16b.in(port_def);
		char * text_data = "  \0";
		text_data[0] = (data>>8) & 0xFF;
		text_data[1] = data & 0xFF;
	//	printf(text_data);
    }	

}
char* AdvancedTechnologyAttachment::Read28(uint8_t sectorNum,uint32_t count)
{
	if(!(accesible))
	{
		printf("Failed : Not Accessible");
		while(true);
	}
	if(sectorNum > 0x0FFFFFFF)
        while(true);
	//Identify What 
	//Drive You want to comunicate with
	//MASTER || SLAVE
	if(this->type == MASTER)
 		p8b.out(0xE0 | ((sectorNum & 0x0F000000) >> 24),port_def + 0x6);
	else
		p8b.out(0xF0 | ((sectorNum & 0x0F000000) >> 24),port_def + 0x6);

	p8b.out(0,port_def + 0x1);
	p8b.out(1,port_def + 0x2);
	p8b.out( sectorNum & 0x000000FF,port_def + 0x3);
	p8b.out((sectorNum & 0x0000FF00) >> 8,port_def + 0x4);
	p8b.out((sectorNum & 0x00FF0000) >> 16,port_def + 0x5);
	p8b.out(0x20,port_def + 0x7); //READ COMMAND


    uint8_t status = p8b.in(port_def + 0x7);
    while(((status & 0x80) == 0x80)
       && ((status & 0x01) != 0x01))
        status = p8b.in(port_def + 0x7);

     if(status & 0x01)
    {
        printf("ERROR");
        while(true);
    }

//     printf("\nReading ATA Drive: ");
  char return_text[999]="";  
  uint32_t count_index=0;

     for(uint32_t i = 7; i < count; i += 2)
    {
        uint16_t wdata = p16b.in(port_def);
        
        char *text = "  \0";
        //printf("%c" , wdata & 0xFF);
        text[0] = wdata & 0xFF;
        return_text[count_index] = wdata & 0xFF;
        count_index++;
        
        if(i+1 < count)
        {
           // printf("%c" , (wdata >> 8) & 0xFF);
            text[1] = (wdata >> 8) & 0xFF;
            return_text[count_index] = (wdata >> 8) & 0xFF;
             count_index++;
        }
        else
            text[1] = '\0';
    }      

    for(int i = count + (count%2); i < 512; i += 2)
        p16b.in(port_def);
   return (char*)return_text;
}
void AdvancedTechnologyAttachment::Write28(uint8_t sectorNum, char* data, uint32_t start, uint32_t count)
{
	if(!(accesible))
	{
		printf("Failed : Not Accessible");
		return;
	}
		//Larger Addressing Than 28
	//check first 4 bits are 0
	if(sectorNum > 0x0FFFFFFF)
		return;

	if(count>512)
		return;
//Identify What 
	//Drive You want to comunicate with
	//MASTER || SLAVE
	if(this->type == MASTER)
 		p8b.out(0xE0 | ((sectorNum & 0x0F000000) >> 24),port_def + 0x6);
	else
		p8b.out(0xF0 | ((sectorNum & 0x0F000000) >> 24),port_def + 0x6);
    
    

	p8b.out(0,port_def + 0x1);
	p8b.out(1,port_def + 0x2);
	p8b.out( sectorNum & 0x000000FF,port_def + 0x3);
	p8b.out((sectorNum & 0x0000FF00) >> 8,port_def + 0x4);
	p8b.out((sectorNum & 0x00FF0000) >> 16,port_def + 0x5);
	p8b.out(0x30,port_def + 0x7); //WRITE COMMAND

    

 for(uint32_t i = start; i < count; i += 2)
    {
        uint16_t wdata = data[i];
        if(i+1 < count)
            wdata |= ((uint16_t)data[i+1]) << 8;
        p16b.out(wdata,port_def);
        
        char *text = "  \0";
        text[0] = (wdata >> 8) & 0xFF;
        text[1] = wdata & 0xFF;
 //       printf(text);
    }
    
    for(int i = count + (count%2); i < 512; i += 2)
    	p16b.out(0x0000,port_def);

 //   printf("\n");
        
}
void AdvancedTechnologyAttachment::Flush()
{
	if(!(accesible))
	{
		printf("Failed : Not Accessible");
		return;
	}
	if(this->type == MASTER)
 		p8b.out(0xE0,port_def + 0x6);
	else
		p8b.out(0xF0,port_def + 0x6);


    p8b.out(0xE7,port_def + 0x7);

    uint8_t status = p8b.in(port_def + 0x7);
    if(status == 0x00)
        return;
    
    while(((status & 0x80) == 0x80)
       && ((status & 0x01) != 0x01))
        status = p8b.in(port_def + 0x7);
        
    if(status & 0x01)
    {
        printf("ERROR FLUSH");
        return;
    }
}