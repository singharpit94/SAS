import java.io.IOException;
import java.util.Scanner;
/* Java program to handle multiple catch statement
 * written by
 * Arpit Kumar Singh
 * 13/CS/31
 */
public class Multiple_Catch {
	public static int  mul_catch(int div_value,int array[])
	{  
		int return_value=0;
		try{
			//array intialisation with default values
			for(int i=0;i<array.length;i++)
				array[i]/=div_value;
			System.out.println("out of bounds"+array[array.length]);
			
		} catch(ArithmeticException e){
			//Arithmetic Exception when denominator is zero
			System.out.println("Divide by Zero\n");
			return_value=1;
			
		}
		catch(ArrayIndexOutOfBoundsException f){
			//Array Index Out of Bounds Exception when index is out of bound
			System.out.println("out of bounds\n");
			return_value=2;
		}
		finally
		{   //return value in finally
			System.out.println("Everything perfect\n");
			return return_value;
		}
	}
}
