#include "kbd.h"

typedef void(*regs_func)(struct regs *r);

static PORT::Port8Bits p8b_kbd_drv;

static bool shift = false;

extern void install_handler_irq(int irq, regs_func handler);

bool enter_presed;

static int total_typed=0;

SerialPort sp_kbd;

/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
unsigned char kbdus[183] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   1,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   2,				/* Right shift */	
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

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

    struct enter_pressed_structure kbd_str_e;
    struct val_e val_e_inst;
  };

void kbd_init()
{
	//
	kbdus[182] = 109;
	kbdus[170] = 110;
}
/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r)
{
    unsigned char scancode;

    /* Read from the keyboard's data buffer */
    scancode = p8b_kbd_drv.in(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */

        switch(scancode)
        {
        	case 170:
        	case 182:
        		shift = false;
        		break;
        	case 186:
        		if(shift == false)
        			shift = true;
        		else
        			shift = false;
        		break;
		}
    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative andlos
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */

        switch(kbdus[scancode])
        {
        	case '\b':
	        	//Use Build in Printf Backspace
        		total_typed--;
        		sp_kbd.write_number_serial(total_typed);

        		if(!(total_typed<0))
        		{
        			printf("\b");
        			enter_press_np::val_e_inst.val_e[enter_press_np::val_e_inst.index_val_e] = (char) 0;
        			enter_press_np::val_e_inst.index_val_e--;
        		}
	        	break;
        	case ' ':
        		total_typed++;
        		enter_press_np::val_e_inst.val_e[enter_press_np::val_e_inst.index_val_e] = (char)kbdus[scancode];
        		enter_press_np::val_e_inst.index_val_e++;
        		printf(" ");
        		break;
	        case 1:
	        case 2:
	        	shift = true;
	        	break;	
	        default:
	       		if( ((int)kbdus[scancode]) >= 97 && ((int)kbdus[scancode]) <= 122)
	       		{
	       			total_typed++;
                    enter_press_np::val_e_inst.val_e[enter_press_np::val_e_inst.index_val_e] = (char)kbdus[scancode];
                    enter_press_np::val_e_inst.index_val_e++;

	    			if(shift == false)
	        			printf("%c" , kbdus[scancode]);
	        		else
	        		{
	        			printf("%c" ,toUpper(kbdus[scancode]));
	        		}
	       		}
	        	break;	
        }


        switch((int)scancode)
        {
           case 28:
                enter_presed = true;
                break;
        }
    }
}

void emptyString(char* str)
{
	for(int i=0; str[i]!='\0'; i++)
	{
		str[i] = (char) 0;
	}
}
enter_press_np::enter_pressed_structure enter_pressed_func()
{
    if(enter_presed == true)
    {
        enter_press_np::kbd_str_e.bit = 0;
        //Bug Fix
        if(enter_press_np::val_e_inst.val_e[enter_press_np::val_e_inst.index_val_e] == 'P')
        {
            enter_press_np::val_e_inst.val_e[enter_press_np::val_e_inst.index_val_e] = (char) 0;
            enter_press_np::val_e_inst.index_val_e--;
        }

        if(Lib::str::strlen(enter_press_np::val_e_inst.val_e) > (unsigned)enter_press_np::val_e_inst.index_val_e)
        {
        	int index_start = (unsigned)enter_press_np::val_e_inst.index_val_e;
        	int index_stop = Lib::str::strlen(enter_press_np::val_e_inst.val_e);
             for(int i=index_start; i<=index_stop; i++)
             {
                 enter_press_np::val_e_inst.val_e[i] = (char) 0;
             }
        }

        /*
         * Reset Total Typed
         */
        total_typed=0;

    }
    else
    {
        enter_press_np::kbd_str_e.bit = 1;
        enter_press_np::kbd_str_e.value = enter_press_np::val_e_inst.val_e;
        enter_press_np::val_e_inst.val_e= "";
    }

    enter_presed = false;
    //enter_press_np::val_e_inst.index_val_e = 0;
    return enter_press_np::kbd_str_e;
}


void KBD::install_kbd_driver()
{
    install_handler_irq(1, keyboard_handler);
}
