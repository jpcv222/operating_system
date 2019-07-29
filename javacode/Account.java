//---------------------------------------------------------------
//File Account.java
//-----------------------------------------------------------------

import java.io.*;
// jtux is the library that gives the POSIX interface.
import jtux.*;


public class Account {
       
        // helper function to convert int to an array of 4 bytes.
       // This function is needed to write ints to shared memory. 
        private	static final byte[] intToByteArray(int value) {
		return new byte[] {
			(byte)(value >>> 24),
			(byte)(value >>> 16),
			(byte)(value >>> 8),
			(byte)value};
	}
	
        // helper function to convert an array of 4 bytes to an int.
       // This function is needed to read ints from shared memory. 
        private static final int byteArrayToInt(byte [] b) {
		return (b[0] << 24)
			+ ((b[1] & 0xFF) << 16)
			+ ((b[2] & 0xFF) << 8)
			+ (b[3] & 0xFF);
	}

	private static void proc_A(long account, int loops) { 

             byte[] byte_array  =  new byte[4] ;

	     for (int i = 0; i< loops ; i++){
                   
		   Shared_memory.read(account, byte_array, 4); 
		   int tmp = byteArrayToInt(byte_array);
                   tmp = tmp + 200 ;

		   try{
			 Thread.sleep((long)(Math.random()*500.0),0);
		   } catch (Exception e) {
			 System.out.print("Exception: ");
			 System.out.println(">" + e.toString() + "<");
		   }

		    
                   Shared_memory.write(account, intToByteArray(tmp), 4); 
		   try{
			 Thread.sleep((long)(Math.random()*500.0),0);
		   } catch (Exception e) {
			 System.out.print("Exception: ");
			 System.out.println(">" + e.toString() + "<");
		   }
                  System.out.println (" A have added 200. New balance = "+ tmp);
             }//for
	}//proc_A

	private static void proc_B(long account, int loops) { 

             byte[] byte_array  =  new byte[4] ;

	     for (int i = 0; i< loops ; i++){
                   
		   Shared_memory.read(account, byte_array, 4); 
		   int tmp = byteArrayToInt(byte_array);
                   tmp = tmp + 100 ;
		   try{
			 Thread.sleep((long)(Math.random()*500.0),0);
		   } catch (Exception e) {
			 System.out.print("Exception: ");
			 System.out.println(">" + e.toString() + "<");
		   }
                   Shared_memory.write(account, intToByteArray(tmp), 4); 
		   try{
			 Thread.sleep((long)(Math.random()*500.0),0);
		   } catch (Exception e) {
			 System.out.print("Exception: ");
			 System.out.println(">" + e.toString() + "<");
		   }
                  System.out.println (" B have added 100. New balance = "+ tmp);
             }//for
	}//proc_B

	
	static public void main(String[] args) {
   	    try {
		   long  pid ;
                   int shmid ; 
                   long balance ;
                   byte[] byte_array  =  new byte[4] ;
		   
		   shmid = Shared_memory.create(4); 
		   balance =  Shared_memory.attach(shmid);
                   Shared_memory.write(balance, intToByteArray(1000), 4); 

		   pid = UProcess.fork();
		   if (pid == 0) {
			proc_A(balance, 5);
			Shared_memory.detach(balance);
			UProcess.exit(0);
		   }
		   else{ 
		        System.out.println ("Parent : first child created = "+ pid);
			pid = UProcess.fork() ;
			if (pid == 0){
			     proc_B(balance, 5);
			     Shared_memory.detach(balance);
			     UProcess.exit(0);
			}
			 else{
		           System.out.println ("Parent : second child created = "+ pid);
			}
		   }
		   // parent waits for the 2 children .
		   UExitStatus status = new UExitStatus() ;
		   pid = UProcess.wait(status) ;
		   System.out.println ("Parent : first child terminated = "+ pid);
		   pid = UProcess.wait(status) ;
		   System.out.println ("Parent : second child terminated = "+ pid);
		   
                  // parent reads and prints final balance
                   
		   Shared_memory.read(balance, byte_array, 4); 
		   int final_balance = byteArrayToInt(byte_array);
		   System.out.println ("Parent : final balance  = "+ final_balance);
                  
                  // parent detaches shared memory segment, destroys segment and semaphores 

		   Shared_memory.detach(balance);
		   Shared_memory.destroy(shmid);
		   UProcess.exit(0);
		} catch (Exception e) {
			System.out.print("Exception: ");
			System.out.println(">" + e.toString() + "<");
		} //try-catch
	    }//main
}//Account

