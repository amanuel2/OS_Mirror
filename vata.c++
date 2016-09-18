#include "vata.h"



AdvancedTechnologyAttachment ata(0x00,MASTER); // NULL VALUES

Vata::Vata()
{
    AdvancedTechnologyAttachment atapm(PRIMARY_BUS_ATA,MASTER);
	AdvancedTechnologyAttachment ataps(PRIMARY_BUS_ATA,SLAVE);
	AdvancedTechnologyAttachment atasm(SECONDARY_BUS_ATA,MASTER);
	AdvancedTechnologyAttachment atass(SECONDARY_BUS_ATA,SLAVE);
	atapm.Identify();
	ataps.Identify();
	atasm.Identify();
	atass.Identify();
	
	if(atapm.accesible)
	{
		ata=atapm;
		goto end_valid;
	}
	else if(ataps.accesible)
	{
		ata=ataps;
		goto end_valid;
	}
	else if(atasm.accesible)
	{
		ata=atasm;
		goto end_valid;
	}
	else if(atass.accesible)
	{
		ata=atass;
		goto end_valid;
	}
  printf("NO AVAILABLE HARD DISK");
  while(true);	 
  end_valid:;	 
}

Vata::~Vata()
{

}


AdvancedTechnologyAttachment Vata::return_ata()
{
	return ata;
}
