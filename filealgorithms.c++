#include "filealgorithms.h"

FileAlgo::FileAlgo()
{

}

FileAlgo::~FileAlgo()
{

}

char* FileAlgo::File_to_char(File file)
{
  char return_str[999] = "FSTART_FILE__VALID::NAME=";
  char done[17] = "/ENDFILENAME/END";
  int count=0;
  size_t header_name_size = Lib::str::strlen(file.header.name);
  for(uint32_t i=25; i<=25+header_name_size; i++)
   return_str[i] = file.header.name[i-25];
  for(uint32_t i=25+header_name_size; i<=(25+header_name_size+16);i++)
     return_str[i] = done[count++];
 // printf("%s",return_str);
 return (char*)return_str;
}

File FileAlgo::char_to_File(char* val)
{
  char file_name[500];
  char* start_file = "FSTART_FILE__VALID";
  struct File to_return;
  printf("\n\n\n");
  for(int i=0; i<=17; i++)
    if(val[i]!=start_file[i])
      goto end;
  for(int i=25; val[i]!='/'; i++)
    file_name[i-25] = val[i];
  to_return.header.name = file_name;
  return to_return;
  end:; 
  printf("ERROR CHAR_TO_FILE"); 
  while(true);
}
