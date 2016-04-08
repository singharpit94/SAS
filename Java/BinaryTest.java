/* This is a java class to test Binary Search
Written by Arpit Kumar Singh(13/CS/31)
*/


import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import junit.framework.TestCase;

public class BinaryTest extends TestCase {

	private int[] array;
	private int size;
	private int search;
	public BinaryTest(String testName){
		super(testName);
	}

	//Intialising the array with  default values
	protected void setUp() throws Exception{
		   super.setUp();
		   array=new int[5];
		   for(int i=0;i<5;i++)
			   array[i]=i+1;
		    size=5;
		    search =3;
	   }
	 protected void tearDown() throws Exception{
		   super.tearDown();
		   
		   
	   }
	   //Testing for valid Binary Search
	 public void testBinarySuccess(){
		
		    
		   search =3;  
		   int index =3;
		   int indexreturn=BinarySearch.bsearch(array, size, search);
		   assertEquals(indexreturn,index);
	   }
	   //Testing for Binary Searching invalid
	 public void testBinaryFailed()
	   {
		 
		  search =6;  
		  int index =3;
		  int indexreturn=BinarySearch.bsearch(array, size, search);
		   assertNotSame(indexreturn,index);
	   }
	 public void testBinaryFailed1()
	   {
		 
		  search =6;  
		  int index =-1;
		  int indexreturn=BinarySearch.bsearch(array, size, search);
		   assertEquals(indexreturn,index);
	   }
