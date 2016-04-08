/*Program to implement multilevel inheritance in java
  Written by Arpit Singh(13/CS/31)
  */


//Base Class   
public class Base1 {
	
	    public static int Add(int var1,int var2 )
	    {
	    	return var1+var2;
	    }

}

//Base Class extending Base1
public class Base2 extends Base1 {
	public static int Sub(int var1,int var2)
	{
		return var1-var2;
	}

}

//Derived class extending Base2
public class Derieved extends Base2{
	public static int multiply(int var1,int var2){
		return var1*var2;
	}

}

