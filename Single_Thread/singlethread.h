#ifndef SINGLETHREAD_H
#define SINGLETHREAD_H

#define SAMPLES 5
#define THRESHOLD 60
#define ARRAY_SIZE 160

bool cache [SAMPLES*100]; // True represents flushed, false represents in DRAM
int sender [SAMPLES*100];
int receiver [SAMPLES*100];
int time[SAMPLES*100][SAMPLES];  // index 0 for i, index 1 for time_sender, index 2 for time_STC, index 3 for encrypted
typedef unsigned long long ticks;



#endif 