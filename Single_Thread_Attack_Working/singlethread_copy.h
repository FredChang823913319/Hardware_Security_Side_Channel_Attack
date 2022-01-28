#ifndef SINGLETHREAD_COPY_H
#define SINGLETHREAD_COPY_H

#define SAMPLES 5
#define THRESHOLD 60


bool cache [SAMPLES*100]; // True represents flushed, false represents in DRAM
int sender [700]; // 64 bytes per cache line for intel i7   int: 4 bytes  
int receiver [SAMPLES*100];
int time[SAMPLES*100][SAMPLES];  // index 0 for i, index 1 for time_sender, index 2 for time_STC, index 3 for encrypted
typedef unsigned long long ticks;

void measurement(int l, int i);


#endif 