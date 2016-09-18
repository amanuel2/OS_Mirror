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

class FileAlgo
{
public:
	

	FileAlgo();
	~FileAlgo();
	char* File_to_char(File file);
	File char_to_File(char* val);
	char* return_file_names_from_encoded_char(char *val);	
};

#endif