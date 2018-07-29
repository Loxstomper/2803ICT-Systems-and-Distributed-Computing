#ifndef STUFF_H
#define STUFF_H

void get_platform();
void get_cwd();

#ifdef __linux__
long int get_file_size(const char* f);
#else
long int get_file_size();
#endif

#endif
