#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <x86intrin.h>
#include "receiver_copy.h"




int main() {
  

  int code[10];

  struct stat mystat;
  int *pmap;
  
  int fd;
  fd = open("text.txt", O_RDWR);
   
  if (fd == -1) {
    perror("open");
    exit(1);
  }
  
  if (fstat(fd, &mystat) < 0) {
    perror("fstat");
    close(fd);
    exit(1);
  }

  pmap = mmap(0, mystat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if(pmap == MAP_FAILED){
    perror("mmap");
    close(fd);
    exit(1);
  }

  FILE *fptr = fopen("sample.txt", "w");
  if(fptr ==  NULL){
    printf("Could not open file");
  }


for(int i = 0; i < 100; i++)
{
  ticks tick1, tick2, tick3, tick4;
  unsigned time_sender;
  unsigned time_TSC;
  
  char temp;


  // temp = *pmap;


  //_mm_mfence();                      /* this properly orders both clflush and rdtscp*/
  //_mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
  //tick1 = __rdtsc();                 /* set timer */
  //_mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
 	//code[0] = *(pmap);

  //printf("%c\n",code[0]);
  /* measuring the write miss latency to array is not meaningful because it's an implementation detail and the next write may also miss */
  /* no need for mfence because there are no stores in between */
  //_mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp and the load*/
  //tick2 = __rdtsc();
  //_mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions */
  //time_sender = tick2 - tick1;


  _mm_mfence();                      /* this properly orders both clflush and rdtscp*/
 	_mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
  tick1 = __rdtsc();                 /* set timer */
  _mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
 
	code[0] = *(pmap);

	_mm_mfence();              // prevent clflush from being reordered by the CPU or the compiler in this direction */
  _mm_lfence();  
	tick2 = __rdtsc();
	_mm_lfence();   

  while(1){
  _mm_mfence();              // prevent clflush from being reordered by the CPU or the compiler in this direction */
  _mm_lfence();  
	tick3 = __rdtsc();
	_mm_lfence();   
		if((tick3-tick1) >= 5000){break;}
  }
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
  


  

  printf("time_sender = %u, time_TSC = %u\n", time_sender, time_TSC);
  time[i][0] = i;
	time[i][1] = time_sender;
	time[i][2] = time_TSC;
  if(time_sender > time_TSC){
    time_sender = time_sender - time_TSC;
  }
  else{
    time_sender = 0;
  }
  printf("time_sender2 = %u\n", time_sender);
  if (time_sender > THRESHOLD){
    receiver[0] = 1;
    cache[0] = 1;
    time[i][3] = 1;
    //fprintf(fptr, "1\n");
    printf("1\n");
  }
  else{
    receiver[0] = 0;
    cache[0] = 0;
    time[i][3] = 0;
    printf("0\n");
    //fprintf(fptr, "0\n");
  }

  

}
  for(int i = 0; i < 100; i++){
		fprintf(fptr, "%u, %u, %u, %u\n", time[i][0], time[i][1],time[i][2],time[i][3]);
	}
  fclose(fptr);

  // munmap(addr, size);
  return 0;

}
