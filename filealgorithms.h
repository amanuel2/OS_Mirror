#ifndef _FILEALGO_H_
#define _FILEALGO_H 1

#include "stdio.h"
#include "stdarg.h"
#include "stdint.h"

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
};

#endif