// Header file for the Shared Memory "easy to use operation".
#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

// This is an interface to the SystemV Shared Memory operations that
// easier to use. If you're interested
// you can take a look here, but you do not need to understand
// the implementation, just the interface.

typedef int Shared_memory;

// Shared_memory_create creates a new shared memory segment.
// Argument size is the size of the segment. 
// Shared_memory_create returns a handle to the newly created
// shared memory segment. When the OS is not able to create a new 
// segment, the process is terminated with exit value 1.
Shared_memory Shared_memory_create(int size);


// Shared_memory_destroy removes the shared memory segment in argument.
// If the argument shm is not a valid handle to a shared memory segment
// the process is terminated with exit value 1.
// You should always remove a shared memory segment when you are finished
// with it.
void Shared_memory_destroy(Shared_memory shm);


// Shared_memory_attach "places" the shared memory segment passed in argument 
// in the address space of the calling process. This way the process can
// access the segment.  A pointer to the the segment in the process address space 
// is returned.
// If the argument shm is not a valid handle to a shared memory segment
// the process is terminated with exit value 1.
void * Shared_memory_attach(Shared_memory shm);

// Shared_memory_detach "detaches" the shared memory segment at shmaddr
// in the process's address space.
// If there is no shared memory attached at address shmaddr.
// the process is terminated with exit value 1.
void Shared_memory_detach(const void *shmaddr);

#endif
