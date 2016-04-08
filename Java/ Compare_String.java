/*This is a CLass to compare String and StringBuffer
 * Writeen by Arpit Singh(13/CS/31)
 */



public class Compare_String {
	//comparing length function of string and stringBuffer
	public static int compare_string(String s1,StringBuffer s2){
		
		
		int length_1=s1.length();
		int length_2=s2.length();
		
		
		
		return length_1-length_2;
	}
	//comparing concat function of String and StringBuffer
public static int compare_string1(String s1,StringBuffer s2){
		
		
		String s3=s1.concat("Singh");
		int length_1=s3.length();
		StringBuffer s5=new StringBuffer("Singh");
	    StringBuffer s4=s2.append(s5);
	    int length_2=s3.length();
		
		
		
		return length_1-length_2;
	}
	

}