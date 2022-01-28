#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <x86intrin.h>


#include "singlethread.h"

// static __inline__ ticks getticks(void)
// {
//      unsigned a, d;
//      asm("cpuid");
//      asm volatile("rdtsc" : "=a" (a), "=d" (d));

//      return (((ticks)a) | (((ticks)d) << 32));
// }




int main(){
  FILE *fptr = fopen("sample.txt", "w"); 
   
  if (fptr == NULL) { 
    printf("Could not open file"); 
    return 0; 
  } 

  for(int i = 0; i < 100; i++){
    ticks tick1, tick2, tick3, tick4;
    int temp;
    unsigned time_sender; 
    unsigned time_TSC;
  
    for (int j = 0; j < SAMPLES; j++ ){ //bring array data into cache 
      sender[j*16] = j;                 
    }
  
    //Sender
    for(int n = 0; (n < SAMPLES); n++){
      // printf( "address = %p \n", &sender[ i ] ); /* guaranteed to be aligned within a single cache line */
      _mm_mfence();                         // prevent clflush from being reordered by the CPU or the compiler in this direction */  
      _mm_clflush( &sender[n*16] );         // flush the line containing the element */
    }
    
   
    //Receiver 
    for(int l = 0; l < SAMPLES; l++){
  
    
      /* Method 1: with excessive memory fence */
      // _mm_mfence();                      // this properly orders both clflush and rdtscp*/
      // _mm_lfence();                      // mfence and lfence must be in this order + compiler barrier for rdtscp */
      // tick1 = getticks();
      // _mm_lfence();                      // serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
      // temp = sender[ i*16 ];             // array[0] is a cache miss */
     
      // _mm_lfence();                      // mfence and lfence must be in this order + compiler barrier for rdtscp and the load*/
      // tick2 = getticks();    
      // _mm_lfence();                      // serialize __rdtscp with respect to trailing instructions */
      // time_sender = tick2 - tick1;
     
      // _mm_mfence();                      // this properly orders both clflush and rdtscp*/
      // _mm_lfence();                      // mfence and lfence must be in this order + compiler barrier for rdtscp */
      // tick3 = getticks();
      // _mm_lfence();                      // serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
      
    
      // _mm_lfence();                      // mfence and lfence must be in this order + compiler barrier for rdtscp and the load*/
      // tick4 = getticks();    
      // _mm_lfence();                      // serialize __rdtscp with respect to trailing instructions */
      // time_TSC = tick4 - tick3;
  
  
  
  
  
  
  
  
  
  
      /* Method 2: no memory fence */
      // tick1 = getticks();
      // _mm_lfence();                      // serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
      
      
      // temp = sender[i*16];                  // array[0] is a cache miss */
      // _mm_lfence();                      // mfence and lfence must be in this order + compiler barrier for rdtscp and the load*/
  
      // tick2 = getticks();    
      // _mm_lfence();                      // serialize __rdtscp with respect to trailing instructions */
  
      // time_sender = tick2 - tick1;
    
  
  
      // _mm_lfence();                      // mfence and lfence must be in this order + compiler barrier for rdtscp */
      // tick3 = getticks();
      // _mm_lfence();                      // serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
     
     
      // tick4 = getticks();    
      // _mm_lfence();                      // serialize __rdtscp with respect to trailing instructions */
      // time_TSC = tick4 - tick3;
     
  
  
  
      /* Method 3: with built_in function */
      /* rdtscp is not suitbale for measuing very small sections of code because
      the write to its parameter occurs after sampling the TSC and it impacts 
      compiler optimizations and code gen, thereby perturbing the measurement */
  
      _mm_mfence();                      /* this properly orders both clflush and rdtscp*/
      _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
      tick1 = __rdtsc();                 /* set timer */
      _mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
      temp = sender[ l*16 ];             /* array[0] is a cache miss */
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
      time[i*SAMPLES+l][0] = i*SAMPLES + l;
      time[i*SAMPLES+l][1] = time_sender;
      time[i*SAMPLES+l][2] = time_TSC;
  
      // printf("after: %u,%u, %d\n", time_sender, time_TSC, i);
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
        printf("1\n");
        // fprintf(fptr, "1\n");
      }
      else{
        printf("0\n");
        // fprintf(fptr, "0\n");
        time[i*SAMPLES+l][3] = 0;
      }
      
    }
  
  
    
 
  }


  for(int i = 0; i < 500; i++){
    fprintf(fptr, "%u, %u, %u, %u\n", time[i][0], time[i][1],time[i][2],time[i][3]);
  }

  fclose(fptr);
 

}


