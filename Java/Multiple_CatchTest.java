/* This is a class to test Multiple_Catch 
* written by Arpit Kumar Singh(13/CS/31)
*/


import static org.junit.Assert.*;


import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import junit.framework.TestCase;

public class Multiple_CatchTest extends TestCase {
   
	private int[] array;	
	private int divide;	
	public Multiple_CatchTest(String testName){
		super(testName);
	}
	
	@Before
	public void setUp() throws Exception {
		//array intialisation with default values
		array=new int[5];
		for(int i=0;i<5;i++){
			array[i]=i+1;
			
		}
		
	}

	@After
	public void tearDown() throws Exception {
	}
    //Testing Arithmetic Exception
	 public void testArithmeticException(){
			
		    
		   int index =1;
		   divide=0;
		   int indexreturn=Multiple_Catch.mul_catch(divide, array);
		   assertEquals(indexreturn,index);
	   }
	   //Testing ArrayOutofBound Exception
	 public void testArrayOutofBoundecxeption(){
			
		    
		   int index =2;
		   divide=3;
		   int indexreturn=Multiple_Catch.mul_catch(divide, array);
		   assertEquals(indexreturn,index);
	   }

}