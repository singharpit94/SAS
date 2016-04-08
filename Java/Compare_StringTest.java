/* This is a class to test comopare string and string Buffer
   Written by Arpit Singh(13/CS/31)
   */



import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import junit.framework.TestCase;
public class Compare_StringTest extends TestCase {

	
	private String s1;
	private StringBuffer s2;
	public Compare_StringTest(String testName){
		super(testName);
	}
	@Before
	public void setUp() throws Exception {
		s1="Arpit";
		s2=new StringBuffer("Arpit");
	}

	@After
	public void tearDown() throws Exception {
	}
    //testing length function
	@Test
	public void testCompare_string() {
		s1="Arpit";
		s2=new StringBuffer("Arpit");
		int expected_value=0;
		int get_value=Compare_String.compare_string(s1, s2);
		assertEquals(expected_value,get_value);
	}

	//Testing concat function
	@Test
	public void testCompare_string1() {
		s1="Arpit";
		s2=new StringBuffer("Arpit");
		int expected_value=0;
		int get_value=Compare_String.compare_string1(s1, s2);
		assertEquals(expected_value,get_value);
	}

}
