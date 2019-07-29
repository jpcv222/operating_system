/*---------------------------------------------------------------
File shared_memory.c.
Implementation of "easy to use" shared memory operations.
-----------------------------------------------------------------*/

#include "shared_memory.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


// Shared_memory_create creates a new shared memory segment.
// Argument size is the size of the segment in bytes. 
// Shared_memory_create returns a handle to the newly created
// shared memory segment. When the OS is not able to create a new 
// segment, the process is terminated with exit value 1.
Shared_memory Shared_memory_create(int size)
{
     Shared_memory shmid ;

     key_t key = ftok(".", getpid() + (int)(random()*1000));

     if ((shmid = shmget(key, size, IPC_CREAT | 0666)) < 0){
           perror("Unable to create a shared memory segment");
           exit(1);
     }
     return(shmid);
}//Shared_memory_create


// Shared_memory_destroy removes the shared memory segment in argument.
// If the argument shm is not a valid handle to a shared memory segment
// the process is terminated with exit value 1.
// You should always remove a shared memory segment when you are finished
// with it.
void Shared_memory_destroy(Shared_memory shm)
{

     if (shmctl(shm, IPC_RMID, NULL) <0){
           perror("Unable to destroy a shared memory segment");
           exit(1);
     }

}//Shared_memory_destroy


// Shared_memory_attach "places" the shared memory segment passed in argument 
// in the address space of the calling process. This way the process can
// access the segment.  A pointer to the the block in the process address space 
// is returned.
// If the argument shm is not a valid handle to a shared memory segment
// the process is terminated with exit value 1.
void * Shared_memory_attach(Shared_memory shm)
{
    void *shmaddr ;
     
    if ((shmaddr = shmat(shm, NULL, 0)) == (void *)(-1)){
          perror("Unable to attach shared memory segment");
          exit(1);
    }
    return(shmaddr) ;

}//Shared_memory_attach

// Shared_memory_detach "detaches" the shared memory segment at shmaddr
// in the process's address space.
// If there is no shared memory attached at address shmaddr.
// the process is terminated with exit value 1.
void Shared_memory_detach(const void *shmaddr)
{
     
    if (shmdt(shmaddr) < 0) {
          perror("Unable to detach shared memory segment");
          exit(1);
    }
}//shared_memory_detach

