#include "kbd.h"



static PORT::Port8Bits p8b_kbd_drv;

bool shift = false;

extern void install_handler_irq(int irq, regs_func handler);
extern char *itoa(int val);

bool enter_presed;

static int total_typed=0;

SerialPort sp_kbd;

uint8_t scancode;
uint32_t data_key_press[2] = {5,0x00};
bool key_pressed=false;

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

static uint8_t number_shift[10] = 
{
    '!','@','#','$','%','^',
    '&','*','(',')'
};

void kbd_test()
{
	alphabet[222] = 'A';
	kbdus[2222] = 'C';
}

char return_pressed_letter(int scancode)
{
	uint8_t to_return;
  bool valid_key=false;

	if(scancode>=16 && scancode <=25)
	{
    valid_key=true;
		total_typed++;
		if(shift==false)
			to_return = alphabet[scancode-16];
		else
			to_return = toUpper(alphabet[scancode-16]);
	}
	if(scancode>=30 && scancode <=38)
	{
    valid_key=true;
		total_typed++;
		if(shift==false)
			to_return = alphabet[scancode-20];
		else
			to_return = toUpper(alphabet[scancode-20]);
	}
	if(scancode>=44 && scancode <=50)
	{
    valid_key=true;
		total_typed++;
		if(shift==false)
			to_return = alphabet[scancode-25];
		else
			to_return = toUpper(alphabet[scancode-25]);
	}

  if(scancode == 39)
  {
    valid_key=true;
    if(shift==false)
      to_return = ';';
    else
      to_return = ':';
  }

  if(scancode == 40)
  {
    valid_key=true;
    if(shift==false)
      to_return = '\'';
    else
      to_return = '"';
  }
  if(scancode == 41)
  {
    valid_key=true;
    if(shift==false)
      to_return = '`';
    else
      to_return='~';
  }
  if(scancode == 26)
  {
    valid_key=true;
    if(shift==false)
      to_return = '[';
    else
      to_return = '{';
  }
  if(scancode == 27)
  {
    valid_key=true;
    if(shift==false)
      to_return = ']';
    else
      to_return = '}';
  }

 if(scancode == 43)
  {
    valid_key=true;
    if(shift==false)
      to_return = '\\';
    else
      to_return = '|';
  }

if(valid_key==true)
	return to_return;
else
  return '\0';
}

void control_char()
{     
    if(shift == true)
    {
      if(scancode != 11)
        printf("%c" , (number_shift[(((int)scancode)-2)]));
      else
        printf("%c", number_shift[9]);
    }
    else
    {
      if(scancode != 11)
        printf("%d" , (((int)scancode)-1));
    }
}



int intLength(int i) {
    int l=0;
    for(;i;i/=10) l++;
    return l==0 ? 1 : l;
}

/* Handles the keyboard interrupt */
void KBD_NAME::keyboard_handler(struct regs *r)
{
    /* Read from the keyboard's data buffer */
    scancode = p8b_kbd_drv.in(0x60);
    key_pressed = true;

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    	OnKeyUp(scancode);
    else
    	OnKeyDown(scancode);

    return;
}

uint8_t get_scan_code()
{
  if(key_pressed==true)
  {
    key_pressed = false;
    return scancode;
  }
  else
     return 0;
  
}



void KBD_NAME::OnKeyDown(uint8_t scancode)
{
	if((int) scancode == 42)
	   shift = true;

	else if((int) scancode>=16 && (int) scancode <= 50)
	{
		uint8_t letter_key_press = return_pressed_letter(scancode);
	 //   printf("%c" , letter_key_press);
	}
}

void KBD_NAME::OnKeyUp(uint8_t scancode)
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



void emptyString(char* str)
{
	for(int i=0; str[i]!='\0'; i++)
	{
		str[i] = (char) 0;
	}
}

void KBD::install_kbd_driver()
{
    install_handler_irq(1,KBD_NAME::keyboard_handler);
}
