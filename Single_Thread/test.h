#ifndef TEST_H
#define TEST_H

#define DATA_NUM 4
#define THRESHOLD 60
#define ARRAY_SIZE 1600
#define ENCODED_BIT_NUM 100

bool cache [ENCODED_BIT_NUM]; // True represents flushed, false represents in DRAM
int sender [ARRAY_SIZE];
int receiver [ENCODED_BIT_NUM];
int time[ENCODED_BIT_NUM][DATA_NUM];  // index 0 for i, index 1 for time_sender, index 2 for time_STC, index 3 for encrypted
typedef unsigned long long ticks;



#endif 