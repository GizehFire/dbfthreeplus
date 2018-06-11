#ifndef MODUL_H
#define MODUL_H

int Read_dBase3_Header(const char *fileName);
int check_dBase3_version(const char *fileName);
bool is_file_exist(const char *fileName); 
int check_file (const char *fileName, const char *MSG);
int open_success(const char *fileName, const char *MSG); 
int init_lua (const char *fileName);

#endif
