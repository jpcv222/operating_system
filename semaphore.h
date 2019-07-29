// Header file for the Semaphore ADT (Abstract Data Type).
#ifndef SEMAPHORE_H
#define SEMAPHORE_H

// This is an interface to the SystemV semaphores that are
// easier to use. The SystemV interface to semaphores is
// very weird and hard to understand. If you're interested
// you can take a look here, but you do not need to understand
// the implementation, just the interface.

typedef int Semaphore;

// Semaphore_create creates a new semaphore. 
// Argument value is the initial value of the semaphore's counter
// (integer value). For example, value should be 1 for a mutual 
// exclusion semaphore. 
// Semaphore_create returns a handle to the newly created
// semaphore. When the OS is not able to create a new semaphore, 
// the process is terminated with exit value 1.
Semaphore Semaphore_create(int value);


// Semaphore_destroy destroys the semaphore in argument.
// If the argument sem is not a valid Semaphore
// handle, the process is terminated with exit value 1.
// You should always destroy a semaphore when you are finished
// with it.
void Semaphore_destroy(Semaphore sem);

// Semaphore_wait and Semaphore_P do the same thing. They are the 
// Semaphore P operation (of lectures) or semaphore wait operation 
// (of course book).
void Semaphore_wait(Semaphore sem);
void Semaphore_P(Semaphore sem);

// Semaphore_signal and Semaphore_V do the same thing. They are
// the semaphore V operation (of lectures) or semaphore signal
// operation (of course book).
void Semaphore_signal(Semaphore sem);
void Semaphore_V(Semaphore sem);

#endif
