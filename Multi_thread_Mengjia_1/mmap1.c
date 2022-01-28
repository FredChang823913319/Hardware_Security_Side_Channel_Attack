#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#include <x86intrin.h>

int main(int argc, char* argv[])
{
  int fd;
  struct stat mystat;
  void *pmap;
	unsigned long long tick1, tick2;
  
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

	
	// _mm_mfence();                      /* this properly orders both clflush and rdtscp*/
  // _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
  // tick1 = __rdtsc();                 /* set timer */
  // _mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
 
	// _mm_clflush(pmap); 
	

	// _mm_mfence();              // prevent clflush from being reordered by the CPU or the compiler in this direction */
  // _mm_lfence();  
	// tick2 = __rdtsc();
	// _mm_lfence(); 
	
	// printf("time_target = %llu", tick2-tick1);  // Around 4323 cycles







  
	// strncpy(pmap, "sfdd", 4);
	_mm_mfence();                      /* this properly orders both clflush and rdtscp*/
  _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
  tick1 = __rdtsc();                 /* set timer */
  _mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
 
	_mm_clflush(pmap); 
	

  while(1){
  _mm_mfence();              // prevent clflush from being reordered by the CPU or the compiler in this direction */
  _mm_lfence();  
	tick2 = __rdtsc();
	_mm_lfence(); 
		if((tick2-tick1) >= 5000){break;}
  }




	_mm_mfence();                      /* this properly orders both clflush and rdtscp*/
  _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
  tick1 = __rdtsc();                 /* set timer */
  _mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
 
	//_mm_clflush(pmap); 
	
  while(1){
  _mm_mfence();              // prevent clflush from being reordered by the CPU or the compiler in this direction */
  _mm_lfence();  
	tick2 = __rdtsc();
	_mm_lfence(); 
		if((tick2-tick1) >= 5000){break;}
  }





	_mm_mfence();                      /* this properly orders both clflush and rdtscp*/
  _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
  tick1 = __rdtsc();                 /* set timer */
  _mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
 
	_mm_clflush(pmap); 

  while(1){
  _mm_mfence();              // prevent clflush from being reordered by the CPU or the compiler in this direction */
  _mm_lfence();  
	tick2 = __rdtsc();
	_mm_lfence(); 
		if((tick2-tick1) >= 5000){break;}
  }




	_mm_mfence();                      /* this properly orders both clflush and rdtscp*/
  _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
  tick1 = __rdtsc();                 /* set timer */
  _mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
 
	//_mm_clflush(pmap); 

  while(1){
  _mm_mfence();              // prevent clflush from being reordered by the CPU or the compiler in this direction */
  _mm_lfence();  
	tick2 = __rdtsc();
	_mm_lfence(); 
		if((tick2-tick1) >= 5000){break;}
  }






	_mm_mfence();                      /* this properly orders both clflush and rdtscp*/
  _mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
  tick1 = __rdtsc();                 /* set timer */
  _mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
 
	//_mm_clflush(pmap); 
	
  while(1){
  _mm_mfence();              // prevent clflush from being reordered by the CPU or the compiler in this direction */
  _mm_lfence();  
	tick2 = __rdtsc();
	_mm_lfence();   
		if((tick2-tick1) >= 5000){break;}
  }








  close(fd);


  return 0;

}
  

  






