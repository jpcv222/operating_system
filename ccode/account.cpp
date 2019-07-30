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
static int duration(int min, int max){
	 static bool first_time = true; 
    if(first_time){
        first_time =  false;
        srand48((int) time(NULL));
    }

    return (int) (min + drand48() * (max - min));
}

void proc_A(int *account, int loops){
	int temp; 
	for (int i ; i< loops; i++){
		printf("Agrego 200 \n", );
		temp = *account + 200; 
		sleep(duration(1,2));
		printf("Estado de cuenta = %d\n", temp);
		} 
}

void proc_B(int *account, int loops){ 
	int temp; 
	for (int i ; i< loops; i++){
		printf("Agrego 300 \n", );
		temp = *account + 300; 
		sleep(duration(1,2));
		printf("Estado de cuenta = %d\n", temp);
		} 
}

int main(void){
	Shared_memory allow_account;
	int *status_account;
	int pid;
	int status;
	
	allow_account = Shared_memory_create(sizeof(int));
	status_account = (int*) Shared_memory_attach (allow_account); 
	*status_account = 100000;
	
	pid = fork();
	
	if(pid==0){
		proc_A(status_account, 5);
		Shared_memory_dettach(status_account);
		exit(0); 
		
		}else{
		printf("Parent: first child created = %d \n", pid);
			pid = fork();
		
			if(pid==0){
			proc_B(status_account, 5);
			Shared_memory_dettach(status_account);
			exit(0); 
			
			}else{
			printf("Parent: first child created = %d \n", pid);
			
				}
			}
			
			pid = wait(&status);
			printf("Parent: first child terminated = %d \n", pid);
			pid = wait(&status);
			printf("Parent: first child terminated = %d \n", pid);
			
			printf("Parent: status_account = %d \n", *status_account);
			exit(0);
	
}
