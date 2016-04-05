/*Program:Junit File for testing nature of roots of Quadratic Equations
 * Author:Arpit Kumar Singh(13/CS/31)
 * Date : 17.02.2016
 */
import static org.junit.Assert.*;
import junit.framework.TestCase;

public class QuadraticRootsTest extends TestCase{

	private double a,b,c;
	public QuadraticRootsTest(String testName){
		super(testName);
	}

	public void setUp() throws Exception {
		
	}

	public void tearDown() throws Exception {
	}

	
	public void testQuadratic1() {
		a=2;b=5;c=3;
		int natureExpected = 1;
		int natureReturned = QuadraticRoots.natureOfRoots(a,b,c);
		assertEquals(natureExpected,natureReturned);
	}
	
	public void testQuadratic2() {
		a=4;b=12;c=9;
		int natureExpected = 0;
		int natureReturned = QuadraticRoots.natureOfRoots(a,b,c);
		assertEquals(natureExpected,natureReturned);
	}
	
	public void testQuadratic3() {
		a=2;b=2;c=3;
		int natureExpected = -1;
		int natureReturned = QuadraticRoots.natureOfRoots(a,b,c);
		assertEquals(natureExpected,natureReturned);
	}

}
