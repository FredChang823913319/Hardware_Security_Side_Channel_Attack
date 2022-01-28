#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <x86intrin.h>


#include "test.h"

int main(){
  FILE *fptr = fopen("sample1.txt", "w"); 
   
  if (fptr == NULL) { 
    printf("Could not open file"); 
    return 0; 
  } 

  ticks tick1, tick2, tick3, tick4;
  int temp;
  unsigned time_sender; 
  unsigned time_TSC;
  
  for (int j = 0; j < ENCODED_BIT_NUM; j++ ){ // bring array data into cache 
    sender[j*16] = j;                         // every cache line is 64 bytes 
  }
  
  //Sender
  for(int n = 0; n < 100; n++){
    if ((n % 2) == 0){
      printf( "address = %p \n", &sender[ n*16 ] ); /* guaranteed to be aligned within a single cache line */
      _mm_mfence();                         // prevent clflush from being reordered by the CPU or the compiler in this direction */  
      _mm_clflush( &sender[n*16] );         // flush the line containing the element */  
    }  
  }
    
   
  

  for(int i = 0; i < ENCODED_BIT_NUM; i++){
    _mm_mfence();                      /* this properly orders both clflush and rdtscp*/
    _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
    tick1 = __rdtsc();                 /* set timer */
    _mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
    temp = sender[ i*16 ];             /* array[0] is a cache miss */
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



    //receiver
    // printf("before: %u,%u, %d\n", time_sender, time_TSC, i);
    // fprintf(fptr, "%u,%u, %u\n", time_sender, time_TSC, i);
    // fprintf(fptr,"%d.%s\n", i, str); 
    if(time_sender > time_TSC){
      time_sender = time_sender - time_TSC;
    }
    else{
      time_sender = 0;
    }
    time[i][0] = i;
    time[i][1] = time_sender;
    time[i][2] = time_TSC;
  
    // printf("after: %u,%u, %d\n", time_sender, time_TSC, i);
    if (time_sender > THRESHOLD){
      receiver[i] = 1;
      cache[i] = 1;
    }
    else{
      receiver[i] = 0;
      cache[i] = 0;
    }
    if (cache[i]) {
      time[i][3] = 1;
      // printf("1\n");
      // fprintf(fptr, "1\n");
    }
    else{
      // printf("0\n");
      // fprintf(fptr, "0\n");
      time[i][3] = 0;
    } 
  }
  
  for(int i = 0; i < 100; i++){
    fprintf(fptr, "%u, %u, %u, %u\n", time[i][0], time[i][1],time[i][2],time[i][3]);
  }

  fclose(fptr);
 

}


