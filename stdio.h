#ifndef _STD_LIB_H_
#pragma once
#define _STD_LIB_H_ 1

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "math.h"
#include "kbd.h"
#include "serial.h"
#include "port.h"






//static int num_count_viedo_memory = 0;

void printf(char *str,...);
void putchar(char str,char next_str,va_list &arg);
char toUpper(char sv);
void putchr_t(char str);
int32_t strlen(int8_t *str);
void strcat(char * Dest, char const * Src);
//int8_t* str_cat(int8_t *dest, const int8_t *src);
void reverse(char str[], int32_t length);
char* itoa(int val);
void cls();
void update_clock_time_taken(int sec);
void mouse_move_print(int x, int y);
void mouse_clear_print(int x, int y);
int scanf_terminal();
char* wait_enter();
void update_cursor(int row, int col);
void check_color(char* str, uint8_t color);
void terminal_bg_fg_ccolor(int width, int height);
#endif
