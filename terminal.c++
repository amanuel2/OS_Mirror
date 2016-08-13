#include "terminal.h"


extern void emptyString(char* str);

extern size_t terminal_row;
extern size_t terminal_column;
extern void terminal_bg_fg_ccolor(size_t width, size_t height, int bg, int fg);

namespace enter_press_np
{
   struct enter_pressed_structure
   {
     int bit;
     char* value;
   };

   struct val_e
   {
     char* val_e;
     int index_val_e = 0;
   };

   extern struct val_e val_e_inst;
}


Terminal::Terminal()
{

}


void Terminal::recieve_input()
{


}


void Terminal::char_handler(char* val)
{
    #ifdef DEBUG_MODE
		printf("\t %s " , val);
	#endif
	//printf("%d" , Lib::str::strcmp(val,"help")==0);
	if(Lib::str::strcmp(val,"help")==0)
	{
			printf(" \n ----Help---- \n");
			printf("Commands : %founder% \n");
			printf("Commands : ccolor , type ccolor --help for More Help\n");
	}
	else if(Lib::str::strcmp(val,"%founder%")==0)
	{
		printf("\n Founder of BoneOS : Amanuel Bogale \n ");
	}
	else if(Lib::str::strcmp(val,"ccolor --help")==0)
	{
		printf(" \n--- CColor (Change Color) --- \n");
		printf("Syntax : ccolor fg bg \n");
		printf("Type in the foreground and background \n");
		printf("Both Are Numbers Ranging From 0 - 15");
	}

	else if(Lib::str::startswith("ccolor",val)==0)
	{
		//ccolor  0   3
		//int start_in = 6;
		//int start_end = Lib::str::strlen(val);
		bool valid = true;
		int turns = 0;
		int fg_bg[2];
		for(int i=6; val[i]!='\0'; i++)
		{
			if(turns == 2)
				goto out;
			if(val[i]!= ' ')
			{
				int cur_val = (int) val[i] - '0';
				fg_bg[turns] = cur_val;
				turns++;
			}
		}

		out:
			for(int i=0; i<2; i++)
			{
				if(!(fg_bg[i] >= 0 && fg_bg[i] <= 15))
				{
					printf(" \n Wrong Utilization. Please type ccolor --help for more info. \n");
					valid = false;
					goto done;
				}
			}
		if(valid==true)
		{
			//printf("%d %d " , terminal_row, terminal_column);
			terminal_bg_fg_ccolor(terminal_row*2,terminal_column*2,fg_bg[1], fg_bg[0]);
		}
		done:
			printf("");
	}
}
void Terminal::terminal_initalize()
{
		cls();
		char* val_now;

		printf(" ************     **********       **       * 	 ********		\n");
		printf(" *		  *     *	    *       * *      *      *				\n");
		printf(" *		  *     *	    *       *  *     *      *				\n");
		printf(" *	  	*     *	    *       *   *    *      *					\n");
		printf(" *   ********     *	    *       *    *   *      *****		    \n");
		printf(" *	  	*     *	    *       *     *  *      *					\n");
		printf(" *	  	*     *	    *       *      * *      *					\n");
		printf(" *	  	*     *	    *       *       **      *					\n");
		printf(" ************     **********       *        *      ******** 	\n");



		printf("BoneOS Non-Profit Organization \n");
		printf("For Help type in help, on the Boner \n");
	while(true)
	{		
		printf(" \n<\\User>");

//		check_color("Hello World" , 0xFF3);
		val_now = wait_enter();	

		this->char_handler(val_now);

		emptyString(enter_press_np::val_e_inst.val_e);
		enter_press_np::val_e_inst.index_val_e = 0;

	}

}


Terminal::~Terminal()
{

}
