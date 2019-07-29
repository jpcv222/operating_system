// Implementation of the Semaphore ADT (Abstract Data Type).

#include "semaphore.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#ifndef __APPLE__
// Argument type for 'semctl', not specified in header files...
typedef union {
  int             val;
  struct semid_ds *buf;
  ushort_t        *array;
} semun;
#endif

int Semaphore_create(int value) {
  int semid = 0;
  semid = semget(IPC_PRIVATE,
         1,
         IPC_CREAT | 00400 | 00200);
  if (semid < 0) {
    perror("Semaphore_create");
    exit(1);
  }
  semun arg;
  arg.val = value;
  if (semctl(semid, 0, SETVAL, arg) < 0) {
    perror("Semaphore_create");
    exit(1);
  }
  return semid;
}

void Semaphore_destroy(Semaphore sem) {
  if (semctl(sem, 0, IPC_RMID) < 0) {
    perror("Semaphore_destroy");
    exit(1);
  }
}

void Semaphore_P(Semaphore sem) {
  struct sembuf wait;
  wait.sem_num = 0;
  wait.sem_op = -1;
  wait.sem_flg = 0;
  if (semop(sem, &wait, 1) < 0) {
    perror("Semaphore_wait");
    exit(1);
  }
}

void Semaphore_wait(Semaphore sem) {
  struct sembuf wait;
  wait.sem_num = 0;
  wait.sem_op = -1;
  wait.sem_flg = 0;
  if (semop(sem, &wait, 1) < 0) {
    perror("Semaphore_wait");
    exit(1);
  }
}

void Semaphore_V(Semaphore sem) {
  struct sembuf signal;
  signal.sem_num = 0;
  signal.sem_op = 1;
  signal.sem_flg = 0;
  if (semop(sem, &signal, 1) < 0) {
    perror("Semaphore_signal");
    exit(1);
  }
}

void Semaphore_signal(Semaphore sem) {
  struct sembuf signal;
  signal.sem_num = 0;
  signal.sem_op = 1;
  signal.sem_flg = 0;
  if (semop(sem, &signal, 1) < 0) {
    perror("Semaphore_signal");
    exit(1);
  }
}
