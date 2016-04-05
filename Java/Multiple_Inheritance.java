/* This is a class for Multiple_Inheritance which will implement Base1 and Base2
  * Written by Arpit Kumar Singh(13/CS/31))
*/

public class Multiple_Inheritance implements Base1,Base2{
    //Function to add two integers
	@Override
	public  int Add(int var1, int var2) {
		return var1+var2;
	}
//Function to subtract two integers
	@Override
	public  int sub(int var1, int var2) {
		return var1-var2;
		
	}
	
	
 
}


