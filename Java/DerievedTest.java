import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import junit.framework.TestCase;

public class DerievedTest extends TestCase {
       
	
	
	private int var1;
	private int var2;
	public DerievedTest(String testName)
	{
		super(testName);
	}
	@Before
			
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void testMultiply() {
		var1=3;
		var2=5;
		int expected_value=15;
		int get_value=Derieved.multiply(var1, var2);
		assertEquals(expected_value,get_value);
	}

	@Test
	public void testSub() {
		var1=8;
		var2=5;
		int expected_value=3;
		int get_value=Derieved.Sub(var1, var2);
		assertEquals(expected_value,get_value);
	}

	@Test
	public void testAdd() {
		var1=3;
		var2=5;
		int expected_value=8;
		int get_value=Derieved.Add(var1, var2);
		assertEquals(expected_value,get_value);
	}

}

