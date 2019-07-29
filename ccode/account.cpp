/*---------------------------------------------------------------
File account.c
-----------------------------------------------------------------*/

#include "semaphore.h" // You will need this to use semaphores
#include "shared_memory.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Create a random sleep-time (to induce unpredictability)

static int duration(int min, int max)
{
  static bool first_time = true;

  // Seed the random number generator with the current time
  // of day if we haven't done so yet.
  if (first_time) {
    first_time = false;
    srand48((int) time(NULL));
  }
  return (int) (min + drand48()*(max - min));
}

void proc_A(int *account, int loops)
{ 
    int tmp ;

    for (int i = 0; i< loops ; i++){
      printf("A adds 200 : ");
      tmp = *account + 200 ;
      sleep(duration(1,2));
      *account = tmp ;
      printf(" new balance = %d\n", tmp);
    } 
}

void proc_B(int *account, int loops)
{ 
    int tmp ;
    for (int i = 0; i< loops ; i++){
      printf("B adds 100 ");
      tmp = *account + 100 ;
      sleep(duration(1,2));
      *account = tmp ;
      printf(" new balance = %d\n", tmp);
    } 
}

int main(void)
{
   Shared_memory shmid ; 
   int *balance ;
   int pid ;
   int status ;


   shmid = Shared_memory_create(sizeof(int)); 
   balance = (int *) Shared_memory_attach(shmid);
   *balance = 1000 ; 

   pid = fork();
   if (pid == 0) {
	proc_A(balance, 5);
        Shared_memory_detach(balance);
	exit(0);
   }
   else{ 
        printf (" Parent : first child created = %d \n", pid);
        pid = fork() ;
        if (pid == 0){
             proc_B(balance, 5);
             Shared_memory_detach(balance);
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
   printf ("Parent : Final balance = %d\n", *balance);
   Shared_memory_detach(balance);
   Shared_memory_destroy(shmid);
   exit(0);
}
