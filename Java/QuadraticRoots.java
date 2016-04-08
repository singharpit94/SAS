/*Program:Nature of Quadratic Roots
 * Author:Arpit Kumar Singh(13/CS/31)
 * Date:17.02.2016
 * Input: Co-efficients of x^2,x and constant term of a equation of the form 
 * a*x^2+b^x+c=0
 * Output: Nature of the roots
 */

import java.util.Scanner;



public class QuadraticRoots {
	
	public static int natureOfRoots(double a,double b,double c){
		double double_discriminant;
		
		double_discriminant = b*b - 4*a*c;
		
		//mutant 1
		//double_discriminant = b*b +4*a*c;
		
		//mutant 2
		//double_discriminant = b*b - 4*a;
		
		//mutant 3
		//double_discriminant = b*b -4*c*c;
		
		//mutant 4
		//double_discriminant = b*b -4*a*a;
		
		int int_natureOfRoot;
		
		if(double_discriminant>0){
			int_natureOfRoot = 1;
		}else if(double_discriminant==0){
			int_natureOfRoot= 0;
		}else{
			int_natureOfRoot = -1;
		}
		
		return int_natureOfRoot;
	}
	
	public static void main(String[] args){
		
		java.util.Scanner in = new Scanner(System.in);
		
		double var1;//co-efficient of x^2
		double var2;//co-efficient of x
		double var3;//constant term
		
		System.out.println("Enter the co-effiecient of x^2:");
		var1 = in.nextDouble();
		
		System.out.println("Enter the co-effiecient of x:");
		var2 = in.nextDouble();
		
		System.out.println("Enter the constant term:");
		var3 = in.nextDouble();
		
		QuadraticRoots qr = new QuadraticRoots();
		int int_natureOfRoot = qr.natureOfRoots(var1,var2,var3);
		
		if(int_natureOfRoot==1){
			System.out.println("Roots are real and unequal");
			
		}else if(int_natureOfRoot==0){
				System.out.println("Roots are real and equal");
		}else{
				System.out.println("Roots are imaginary");
		}
		
	}

}
