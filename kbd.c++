#include "kbd.h"

typedef void(*regs_func)(struct regs *r);

static PORT::Port8Bits p8b_kbd_drv;

static bool shift = false;

extern void install_handler_irq(int irq, regs_func handler);
extern char *itoa(int val);

bool enter_presed;

static int total_typed=0;

SerialPort sp_kbd;

namespace enter_press_np
{
  struct enter_pressed_structure
  {
    int bit;
    char* value;
  };

  struct val_e
  {
    char* val_e = "";
    int index_val_e = 0;
  };

  struct enter_pressed_structure kbd_str_e;
  struct val_e val_e_inst;
};

static uint8_t kbdus[183] =
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


static uint8_t alphabet[26] =
{
		'q','w','e','r','t','y',
		'u','i','o','p','a','s',
		'd','f','g','h','j','k'
		,'l','z','x','c','v','b',
		'n','m'
};

char return_pressed_letter(int scancode)
{
	uint8_t to_return;

	if(scancode>=16 && scancode <=25)
	{
		total_typed++;
		if(shift==false)
			to_return = alphabet[scancode-16];
		else
			to_return = toUpper(alphabet[scancode-16]);
	}
	if(scancode>=30 && scancode <=38)
	{
		total_typed++;
		if(shift==false)
			to_return = alphabet[scancode-20];
		else
			to_return = toUpper(alphabet[scancode-20]);
	}
	if(scancode>=44 && scancode <=50)
	{
		total_typed++;
		if(shift==false)
			to_return = alphabet[scancode-25];
		else
			to_return = toUpper(alphabet[scancode-25]);
	}

	return to_return;
}



void kbd_init()
{
	//
	kbdus[182] = 109;
	kbdus[170] = 110;
}

int intLength(int i) {
    int l=0;
    for(;i;i/=10) l++;
    return l==0 ? 1 : l;
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
    	if((int) scancode == 42)
    		shift = true;


    	else if((int) scancode>=16 && (int) scancode <= 50)
    	{
        	uint8_t letter_key_press = return_pressed_letter(scancode);
    		printf("%c" , letter_key_press);
    	}

    }
    return;
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
