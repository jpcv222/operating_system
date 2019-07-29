//---------------------------------------------------------------
//File shared_memory.java
//Implementation of "easy to use" shared memory operations.
//-----------------------------------------------------------------
import java.io.*;
// jtux is the library that gives the POSIX interface.
import jtux.*;

// This is an interface to the SystemV shared memory that are
// easier to use. 
// If you're interested  you can take a look here, but you do not need to understand
// the implementation, just the interface.
abstract class Shared_memory {

	// create creates a new shared memory segment.
	// Argument size is the size of the segment in bytes. 
	// create returns a handle to the newly created
	// shared memory segment. When the OS is not able to create a new 
	// segment, the process is terminated with exit value 1.
	static int create(int size) {
                String keystring = new String(".");
	        int shmid = -1 ; 
                long key; 
		try {
		     key = USysVIPC.ftok(".", (int) UProcess.getpid()+(int)(Math.random()*1000.0));
		     shmid = USysVIPC.shmget(key, size, UConstant.IPC_CREAT | 0666);
		} catch (Exception e) {
		    System.out.print("Exception: ");
		    System.out.println(">" + e.toString() + "<");
		    UProcess.exit(1);
		}
	        return(shmid);
	}//create


	// destroy removes the shared memory segment in argument.
	// If the argument shm is not a valid handle to a shared memory segment
	// the process is terminated with exit value 1.
	// You should always remove a shared memory segment when you are finished
	// with it.
	static void destroy(int shm) {
		try {
                     USysVIPC.s_shmid_ds shmds = new USysVIPC.s_shmid_ds();
		     USysVIPC.shmctl(shm, UConstant.IPC_RMID, shmds) ;
		} catch (Exception e) {
		    System.out.print("Exception: ");
		    System.out.println(">" + e.toString() + "<");
		    UProcess.exit(1);
		}
	}//destroy


	// attach "places" the shared memory segment passed in argument 
	// in the address space of the calling process. This way the process can
	// access the segment.  A pointer to the the block in the process address space 
	// is returned.
	// If the argument shm is not a valid handle to a shared memory segment
	// the process is terminated with exit value 1.
	static long attach(int shm) {
		long shmaddr = -1 ;
	     
		try {
		    shmaddr = USysVIPC.shmat(shm, 0, 0) ;
		} catch (Exception e) {
		    System.out.print("Exception: ");
		    System.out.println(">" + e.toString() + "<");
		    UProcess.exit(1);
		}
	        return(shmaddr) ;
	}//attach

	// detach "detaches" the shared memory segment at shmaddr
	// in the process's address space.
	// If there is no shared memory attached at address shmaddr.
	// the process is terminated with exit value 1.
	static void detach(long shmaddr)
	{
     
		try {
		   USysVIPC. shmdt(shmaddr);
		} catch (Exception e) {
		    System.out.print("Exception: ");
		    System.out.println(">" + e.toString() + "<");
		    UProcess.exit(1);
		}
	}//detach

        // write : writes into shared memory segment.
        // writes at address addr datasize bytes of array data 
        static void write(long addr, byte[] data, int datasize){
		UUtil.jaddr_to_seg(addr, data, datasize);
        }//write
        
	// read : reads from a shared memory segment.
        //reads datasize bytes at address addr and stores them in 
        // array data 
        static void read(long addr, byte[] data, int datasize){
		UUtil.jaddr_from_seg(addr, data, datasize);
        }//write
}//Shared_memory

