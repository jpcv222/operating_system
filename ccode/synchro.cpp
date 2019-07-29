/*---------------------------------------------------------------
File synchro.c.
This program uses a semaphore to synchronize 2 processes.
Here we have a one-way synchronization, one process waits 
for the other to arrive at some point in its execution flow. 
-----------------------------------------------------------------*/

#include "semaphore.h" // You will need this to use semaphores

#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Create a random sleep-time (to induce unpredictability)
static int duration(int min, int max){
  static bool first_time = true;
  // Seed the random number generator with the current time
  // of day if we haven't done so yet.
  if (first_time) {
    first_time = false;
    srand48((int) time(NULL));
  }
  return (int) (min + drand48()*(max - min));
}

void proc_A(int loops){ 
    for (int i = 0; i< loops ; i++){
      printf("A-->%d\n", i);
      sleep(duration(1,8));
    } 
}

void proc_B(int loops){ 
    for (int i = 0; i< loops ; i++){
      printf("B-->%d\n", i);
      sleep(duration(1,2));
    } 
}

int main(void){
	
	
	Semaphore sem = Semaphore_create(1);
	
   int pid ;
   int status ;
   pid = fork();
   if (pid == 0) {
	proc_A(5);
	Semaphore_wait(sem);
	exit(0);
   }
   else{ 
        printf (" Parent : first child created = %d \n", pid);
        pid = fork() ;
        if (pid == 0){
             proc_B(5);
             Semaphore_signal(sem);
	     exit(0);
        }
         else{
           printf (" Parent : second child created = %d \n", pid);
        }
   }
   // parent waits for the 2 children and destroys semaphore synchro.
   pid = wait(&status) ;
   printf ("Parent : first child terminated = %d\n", pid);
   pid = wait(&status) ;
   printf ("Parent : second child terminated = %d\n", pid);
   exit(0);
}
