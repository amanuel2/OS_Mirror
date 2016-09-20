#ifndef _FILEALGO_H_
#define _FILEALGO_H_ 1

#include "stdio.h"
#include "stdarg.h"
#include "stdint.h"
#include "string.h"


struct Header
{
	  char* name;
};

struct File
{
	  struct Header header;
	  char* contents;
};
struct char_two_ret
{
  char names_two[99][99];
  uint32_t index_num;
};

struct ret_chr_arr
{
	char str[999];
};

class FileAlgo
{
public:
	

	FileAlgo();
	~FileAlgo();
	ret_chr_arr File_to_char(File file);
	File char_to_File(char* val);
	char* return_file_names_from_encoded_char(char *val);	
	uint32_t number_of_files(char* val);
	char_two_ret  return_file_names_from_encoded_char_multiple(char* val);
};

#endif