/* This is a Class to test Multiple_Inheritance
* Written by Arpit Kumar Singh(13/CS/31)
*/


import static org.junit.Assert.*;


import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import junit.framework.TestCase;

public class Multiple_InheritanceTest extends TestCase {

	private int var1;
	private int var2;
	public Multiple_InheritanceTest(String testName){
		super(testName);
	}
	
	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}
    //Testing for valid condtion add function
	@Test
	public void testAdd() {
		var1=3;
		var2=4;
		int expected_value=7;
		Multiple_Inheritance m=new Multiple_Inheritance();
		int get_value=m.Add(var1, var2);
		assertEquals(expected_value,get_value);
	}
   //Testing for valid Subtract function
	@Test
	public void testSub() {
		var1=5;
		var2=4;
		int expected_value=1;
		Multiple_Inheritance m=new Multiple_Inheritance();
		int get_value=m.sub(var1, var2);
		assertEquals(expected_value,get_value);
	}
	//Testing for invalid Subtract function
	@Test
	public void testSubInvalid() {
		var1=5;
		var2=4;
		int expected_value=3;
		Multiple_Inheritance m=new Multiple_Inheritance();
		int get_value=m.sub(var1, var2);
		assertNotSame(expected_value,get_value);
	}
	//Testing for invalid Add function
	@Test
	public void testSubInvalid() {
		var1=5;
		var2=4;
		int expected_value=3;
		Multiple_Inheritance m=new Multiple_Inheritance();
		int get_value=m.add(var1, var2);
		assertNotSame(expected_value,get_value);
	}

}
