
//---------------------------------------------------------------
//File Semaphore.java
//-----------------------------------------------------------------

import java.io.*;
// jtux is the library that gives the POSIX interface.
import jtux.*;

// This is an interface to the System V semaphores that are
// easier to use. The System V interface to semaphores is
// very weird and hard to understand. If you're interested
// you can take a look here, but you do not need to understand
// the implementation, just the interface.
abstract class Semaphore {

    // Create a new semaphore. value should be its initial
    // value. It should be 1 in most cases. It returns a
    // handle to the semaphore.
    static int create(int value) {
	int semid = 0;
	try {
	    semid = USysVIPC.semget(UConstant.IPC_PRIVATE,
				    1,
				    UConstant.IPC_CREAT | 00400 | 00200);
	    USysVIPC.u_semun_int arg = new USysVIPC.u_semun_int();
	    arg.val = value;
	    USysVIPC.semctl(semid, 0, UConstant.SETVAL, arg);
	} catch (Exception e) {
	    System.out.print("Exception: ");
	    System.out.println(">" + e.toString() + "<");
	    UProcess.exit(1);
	}
	return semid;
    }

    // Destroy a semaphore. This will free the semaphore given
    // as argument. You should always do this when you're finished
    // with a semaphore.
    static void destroy(int sem) {
	try {
	    USysVIPC.u_semun semun = new USysVIPC.u_semun();
	    USysVIPC.semctl(sem, 0, UConstant.IPC_RMID, semun);
	} catch (Exception e) {
	    System.out.print("Exception: ");
	    System.out.println(">" + e.toString() + "<");
	    UProcess.exit(1);
	}
    }

    // Operation P on a semaphore.  Same operation as wait below. Use P
    // if you are familiar with the lectures, and wait if you are familiar with the course
    // book 
    static void P(int sem) {
	USysVIPC.s_sembuf wait[] = new USysVIPC.s_sembuf[1];
	wait[0] = new USysVIPC.s_sembuf();
	wait[0].sem_num = 0;
	wait[0].sem_op = -1;
	wait[0].sem_flg = 000000;
	try {
	    USysVIPC.semop(sem, wait, 1);
	} catch (Exception e) {
	    	    System.out.print("Exception: ");
	    System.out.println(">" + e.toString() + "<");
	    UProcess.exit(1);
	}
    }
    
    // Operation wait on a semaphore.  Same operation as P  above. Use P
    // if you are familiar with the lectures, and wait if you are familiar with the course
    // book 
    // Wait for the semaphore. It will block until the semaphore
    // is available.
    static void wait(int sem) {
	USysVIPC.s_sembuf wait[] = new USysVIPC.s_sembuf[1];
	wait[0] = new USysVIPC.s_sembuf();
	wait[0].sem_num = 0;
	wait[0].sem_op = -1;
	wait[0].sem_flg = 000000;
	try {
	    USysVIPC.semop(sem, wait, 1);
	} catch (Exception e) {
	    	    System.out.print("Exception: ");
	    System.out.println(">" + e.toString() + "<");
	    UProcess.exit(1);
	}
    }

    // Operation V on a semaphore.  Same operation as signal below.
    // Use V if you are familiar with the lectures, and signal if you are familiar with the course
    // book 
    static void V(int sem) {
	USysVIPC.s_sembuf signal[] = new USysVIPC.s_sembuf[1];
	signal[0] = new USysVIPC.s_sembuf();
	signal[0].sem_num = 0;
	signal[0].sem_op = 1;
	signal[0].sem_flg = 000000;
	try {
	    USysVIPC.semop(sem, signal, 1);
	} catch (Exception e) {
	    	    System.out.print("Exception: ");
	    System.out.println(">" + e.toString() + "<");
	    UProcess.exit(1);
	}
    }
    
    // Operation siganal on a semaphore.  Same operation as V above.
    // Use V if you are familiar with the lectures, and signal if you are familiar with the course
    // book 
    static void signal(int sem) {
	USysVIPC.s_sembuf signal[] = new USysVIPC.s_sembuf[1];
	signal[0] = new USysVIPC.s_sembuf();
	signal[0].sem_num = 0;
	signal[0].sem_op = 1;
	signal[0].sem_flg = 000000;
	try {
	    USysVIPC.semop(sem, signal, 1);
	} catch (Exception e) {
	    	    System.out.print("Exception: ");
	    System.out.println(">" + e.toString() + "<");
	    UProcess.exit(1);
	}
    }

}
