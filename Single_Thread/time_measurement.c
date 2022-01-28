#include<sys/time.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>


#include <stdint.h>
#include <x86intrin.h>


#include "time_measurement.h"






static __inline__ ticks getticks(void)
{
     unsigned a, d;
     asm("cpuid");
     asm volatile("rdtsc" : "=a" (a), "=d" (d));

     return (((ticks)a) | (((ticks)d) << 32));
}



// inline void flush(char *adrs) {
//     asm __volatile__ ("mfence\nclflush 0(%0)" : : "r" (adrs) :);
//   }



int main(){
    // int counter;
    // char* ptr;
    ticks tick1, tick2, tick3, tick4, tick5, tick6;
    // unsigned time_100 = 0;
    // unsigned time_200 = 0;
    // unsigned time = 0;
    unsigned time_STC, time_flushing, time_no_flushing;
    // volatile int x = 0;

    int array[100];
    // ptr = (char *)malloc(9);  // Don't do malloc, since malloc has a more complicated cache/memory behaviors 
    // strcpy(ptr, "hardware");



    // tick = getticks();
    // for(counter = 0; counter < 100; counter++){
    //     x++;
    // }
    // tick1 = getticks();

    
    // time_100 = (unsigned)((tick1-tick));
    // printf("num of cycles for 100 cycles: %u\n", time_100);     // num of cycles change based on how many times I run the code ?????
    

    // tick2 = getticks();
    // for(counter = 0; counter < 200; counter++){
    //     x++;
    // }
    // tick3 = getticks();
    // time_200 = (unsigned)((tick3-tick2));
    // printf("num of cycles for 200 cycles: %u\n", time_200);     // num of cycles change based on how many times I run the code ?????
    
    

    // time = (unsigned)((tick1-tick)/2800000000);
    // printf("\ntime in S %u\n",time);


    for ( int i = 0; i < 100; i++ ){ //bring array data into cache 
    array[ i ] = i;                 
    }

    printf( "address = %p \n", &array[ 0 ] ); //guaranteed to be aligned within a single cache line */
    
    _mm_mfence();                      //prevent clflush from being reordered by the CPU or the compiler in this direction */  
    _mm_clflush( &array[ 0 ] ); //flush the line containing the element */
    
    
    
      /* rdtscp is not suitbale for measuing very small sections of code because
       the write to its parameter occurs after sampling the TSC and it impacts 
       compiler optimizations and code gen, thereby perturbing the measurement */

    _mm_mfence();                      // this properly orders both clflush and rdtscp*/
    _mm_lfence();                      // mfence and lfence must be in this order + compiler barrier for rdtscp */
    tick1 = getticks();
    _mm_lfence();                      // serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
    int temp = array[ 0 ];             // array[0] is a cache miss */
   
    _mm_lfence();                      // mfence and lfence must be in this order + compiler barrier for rdtscp and the load*/
    tick2 = getticks();    
    _mm_lfence();                      // serialize __rdtscp with respect to trailing instructions */
    time_flushing = tick2 - tick1;
    printf("num of cycles for flushing: %u\n", time_flushing);     // num of cycles change based on how many times I run the code ?????
      


    _mm_mfence();                      // this properly orders both clflush and rdtscp*/
    _mm_lfence();                      // mfence and lfence must be in this order + compiler barrier for rdtscp */
    tick3 = getticks();
    _mm_lfence();                      // serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
    temp = array[ 0 ];                 // array[0] is in cache */
   
    _mm_lfence();                      // mfence and lfence must be in this order + compiler barrier for rdtscp and the load*/
    tick4 = getticks();    
    _mm_lfence();                      // serialize __rdtscp with respect to trailing instructions */
    time_no_flushing = tick4 - tick3;
    printf("num of cycles for not flushing: %u\n", time_no_flushing);     // num of cycles change based on how many times I run the code ?????







return 0;
}