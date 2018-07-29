#ifndef GETTING_TIME_H
#define GETTING_TIME_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
#include <time.h>
void start_timer(struct timespec* before);
unsigned long stop_timer (struct timespec* before);
void current_time();
#else

#include <windows.h>

#endif
#endif
