#include "terminal.h"

Terminal::Terminal()
{

}


void Terminal::recieve_input()
{


}


void Terminal::char_handler(char* val)
{
	printf("\t %s " , val);
	//printf("%d" , Lib::str::strcmp(val,"help")==0);
	if(Lib::str::strcmp(val,"help")==0)
	{
			printf("Help\n");
			printf("----\n");
			printf("Help Under Construction\n");
	}
}
void Terminal::terminal_initalize()
{
		cls();
		char* val_now;

		printf(" ************  *********** \n");
		printf(" *		  	*  * 		 * \n");
		printf(" *		  	*  * 		 * \n");
		printf(" *		  	*  * 		 * \n");
		printf(" *   ********  * 		 * \n");
		printf(" *		  	*  * 		 * \n");
		printf(" *		  	*  * 		 * \n");
		printf(" *		  	*  * 		 * \n");
		printf(" ************  *********** \n");



		printf("BoneOS Non-Profit Organization \n");
		printf("For Help type in help, on the Boner \n");
	while(true)
	{		
		printf(" \n<\\User>");
		val_now = wait_enter();	

		this->char_handler(val_now);

	}

}


Terminal::~Terminal()
{

}