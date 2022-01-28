#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <x86intrin.h>


#include "singlethread_copy.h"


int main(){
  FILE *fptr = fopen("sample.txt", "w"); 
   
  if (fptr == NULL) { 
    printf("Could not open file"); 
    return 0; 
  } 

  for(int i = 0; i < 100; i++){  
    for (int j = 0; j < SAMPLES; j++ ){ // bring array data into cache   
      sender[j*16*10] = j;           // flush one per every 10 cache lines to prevent hardware adjanency prefetching 
    }
  
    //Sender
    _mm_mfence();                         // prevent clflush from being reordered by the CPU or the compiler in this direction */  
    _mm_clflush( &sender[0*16*10] );

    _mm_mfence();                         // prevent clflush from being reordered by the CPU or the compiler in this direction */  
    _mm_clflush( &sender[2*16*10] );

    // for(int n = 0; (n < SAMPLE); n++){
    //   // printf( "address = %p \n", &sender[ i ] ); /* guaranteed to be aligned within a single cache line */
    //   _mm_mfence();                         // prevent clflush from being reordered by the CPU or the compiler in this direction */  
    //   _mm_clflush( &sender[n*16*10] );         // flush the line containing the element */
    // }
    
   if (i%5 == 0){ 
    measurement(0, i);
    measurement(3, i);
    measurement(2, i);
    measurement(4, i);
    measurement(1, i);
   }
   else if (i%5 == 1){   
    measurement(1, i);
    measurement(4, i);
    measurement(2, i);
    measurement(0, i);
    measurement(3, i);
   }
   else if (i%5 == 2){
    measurement(2, i);
    measurement(4, i);
    measurement(1, i);
    measurement(0, i);
    measurement(3, i);
   }
   else if (i%5 == 3){
    measurement(3, i);
    measurement(4, i);
    measurement(1, i);
    measurement(2, i);
    measurement(0, i);   
   }
   else if (i%5 == 4){
    measurement(4, i);
    measurement(1, i);
    measurement(2, i);
    measurement(0, i);
    measurement(3, i);
   }
   

  }

  for(int i = 0; i < 500; i++){
    fprintf(fptr, "%u, %u, %u, %u\n", time[i][0], time[i][1],time[i][2],time[i][3]);
  }

  fclose(fptr);
 

}







void measurement(int l, int i){
  ticks tick1, tick2, tick3, tick4;
  int temp;
  unsigned time_sender; 
  unsigned time_TSC;

  _mm_mfence();                      /* this properly orders both clflush and rdtscp*/
  _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
  tick1 = __rdtsc();                 /* set timer */
  _mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
  temp = sender[ l*16*10];             /* array[0] is a cache miss */
  /* measring the write miss latency to array is not meaningful because it's an implementation detail and the next write may also miss */
  /* no need for mfence because there are no stores in between */
  _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp and the load*/
  tick2 = __rdtsc();
  _mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions */
  time_sender = tick2 - tick1;
  
    
  
  _mm_mfence();                      /* this properly orders both clflush and rdtscp*/
  _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
  tick3 = __rdtsc();                 /* set timer */
  _mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp */
  /* no need for mfence because there are no stores in between */
  _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
  tick4 = __rdtsc();
  _mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions */
  time_TSC = tick4 - tick3;
    
  if(time_sender > time_TSC){
    time_sender = time_sender - time_TSC;
  }
  else{
    time_sender = 0;
  }
  time[i*SAMPLES+l][0] = i*SAMPLES + l;
  time[i*SAMPLES+l][1] = time_sender;
  time[i*SAMPLES+l][2] = time_TSC;

  
  if (time_sender > THRESHOLD){
    receiver[i*SAMPLES+l] = 1;
    cache[i*SAMPLES+l] = 1;
  }
  else{
    receiver[i*SAMPLES+l] = 0;
    cache[i*SAMPLES+l] = 0;
  }
  if (cache[i*SAMPLES+l]) {
    time[i*SAMPLES+l][3] = 1;
    // printf("1\n");
   
  }
  else{
    // printf("0\n");
    time[i*SAMPLES+l][3] = 0;
  }
 
}

