
/*---------------------------------------------------------------
File: Synchro.cpp
Author: Juan Pablo Castro <jpcv222>
Date: 29-07-2019
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
    if(first_time){
        first_time =  false;
        srand48((int) time(NULL));
    }

    return (int) (min + drand48() * (max - min));
}

void proc_A(int loops){
    for(int i=0; i<loops; i++){
        printf("Soy A iteración %d\n", i);
        sleep(1);
    }
}

void proc_B(int loops){
    for(int i=0; i<loops; i++){
        printf("Soy B iteración %d\n", i);
        sleep(1);
    }
}

int main(void){

   Semaphore sem = Semaphore_create(1);
	
   int pid;
   int status;
   
   pid = fork();

   if(pid == 0){
        proc_A(5);
	Semaphore_wait(sem);
        exit(0);
   }
   else {
	printf("Parent: second child created = %d \n", pid);

 	pid = fork();
	if(pid == 0){
		proc_B(5);
		Semaphore_signal(sem);
		exit(0);
	   }
	   else {
		printf("Parent: second child created = %d \n", pid);
	   }
   }

	pid = wait(&status);
	printf("Parent: first child terminated = %d \n", pid);
	pid = wait(&status);
	printf("Parent: first child terminated = %d \n", pid);
	exit(0);
	
}


