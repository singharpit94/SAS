/* This is a class to test Dynamic Dispatch in java
 Written by Arpit Kumar Singh
 */
import static org.junit.Assert.*;


import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import junit.framework.TestCase;

public class BabydogTest extends TestCase {
     
	 public BabydogTest(String testName){
		 super(testName);
	 }
	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}
    //Creating Animal Object and testing food function
	@Test
	public void testFood() {
	    Animal a1=new Animal();
	    String test="Depends";
	    String get=a1.food();
	    assertEquals(test,get);
	    		
	}
	  //Creating Dog Object and testing food function
	@Test
	public void testFoodDog() {
	    Animal a2=new Dog();
	    String test="Meat";
	    String get=a2.food();
	    assertEquals(test,get);
	    		
	}
	  //Creating BabyDog Object and testing food function
	@Test
	public void testFoodBabyDog(){
	    Animal a1=new Babydog();
	    String test="Milk";
	    String get=a1.food();
	    assertEquals(test,get);
	    		
	}

}
