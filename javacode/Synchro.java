//---------------------------------------------------------------
//File Synchro.java
//-----------------------------------------------------------------

import java.io.*;
// jtux is the library that gives the POSIX interface.
import jtux.*;


public class Synchro {

       static void proc_A(int loops) { 
	    for (int i = 0; i< loops ; i++){
	      System.out.println ("A--> "+ i);
              try{
	         Thread.sleep((long)(Math.random()*5000.0),0);
              } catch (Exception e) {
                 System.out.print("Exception: ");
                 System.out.println(">" + e.toString() + "<");
              }
	    } 
	}

	static void proc_B(int loops) { 
	    for (int i = 0; i< loops ; i++){
	      System.out.println ("B--> "+ i);
              try{
	         Thread.sleep((long)(Math.random()*1000.0),0);
              } catch (Exception e) {
                 System.out.print("Exception: ");
                 System.out.println(">" + e.toString() + "<");
              }
	    } 
	}
	
	static public void main(String[] args) {
   	    try {
		   long  pid ;

		   pid = UProcess.fork();
		   if (pid == 0) {
			proc_A(5);
			UProcess.exit(0);
		   }
		   else{ 
		        System.out.println ("Parent : first child created = "+ pid);
			pid = UProcess.fork() ;
			if (pid == 0){
			     proc_B(5);
			     UProcess.exit(0);
			}
			 else{
		           System.out.println ("Parent : second child created = "+ pid);
			}
		   }
		   // parent waits for the 2 children and destroys semaphore sync.
		   UExitStatus status = new UExitStatus() ;
		   pid = UProcess.wait(status) ;
		   System.out.println ("Parent : first child terminated = "+ pid);
		   pid = UProcess.wait(status) ;
		   System.out.println ("Parent : second child terminated = "+ pid);
		   UProcess.exit(0);
		} catch (Exception e) {
			System.out.print("Exception: ");
			System.out.println(">" + e.toString() + "<");
		} //try-catch
	    }//main
}//Synchro
