#include "filealgorithms.h"




FileAlgo::FileAlgo()
{

}

FileAlgo::~FileAlgo()
{

}

ret_chr_arr FileAlgo::File_to_char(File file)
{
  //LANA = Label Name
  struct ret_chr_arr rca;
  char return_str[999] = "FSTART_FILE__VALID::LANA=";
  for(uint32_t i=0; i<=25; i++)
  {
    rca.str[i] = return_str[i];
  }
  char done[17] = "/ENDFILENAME/CEF";
  int count=0;
  size_t header_name_size = Lib::str::strlen(file.header.name);
  for(uint32_t i=25; i<=25+header_name_size; i++)
   rca.str[i] = file.header.name[i-25];
  for(uint32_t i=25+header_name_size; i<=(25+header_name_size+16);i++)
     rca.str[i] = done[count++];     
 return rca;
}

File FileAlgo::char_to_File(char* val)
{
  char file_name[500];
  char* start_file = "FSTART_FILE__VALID";
  struct File to_return;
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

char* deblank(char* input)                                         
{
    int i,j;
    char *output=input;
    for (i = 0, j = 0; i<(signed)Lib::str::strlen(input); i++,j++)          
    {
        if (input[i]!=' ')                           
            output[j]=input[i];                     
        else
            j--;                                     
    }
    output[j]=0;
    return output;
}

char* FileAlgo::return_file_names_from_encoded_char(char *val)
{
  char* name="";
  char* val_temp = val;
  File file_temp = this->char_to_File(val_temp);
  name = file_temp.header.name;
  return deblank(name);
}



char_two_ret FileAlgo::return_file_names_from_encoded_char_multiple(char* val)
{
  uint32_t num_files = this->number_of_files(val);
  char_two_ret ctr;
  uint32_t index_names = 0;
  for(uint32_t i=0; i<Lib::str::strlen(val); i++)
  {
    if(val[i]=='L' && val[i+1]=='A' && val[i+2]=='N'
        && val[i+3]=='A' && val[i+4]=='=')
    {
      index_names++;
      uint32_t start = i+5;
      int start_index=0;
      while(val[start]!='/')
      {
        ctr.names_two[index_names][start_index] = val[start];
        start++;
        start_index++;
      }
    }  
  }
 ctr.index_num = index_names; 
 return ctr;
}

uint32_t FileAlgo::number_of_files(char* val)
{
  return (uint32_t)(Lib::str::count_substr(val,"/CEF",true));
}