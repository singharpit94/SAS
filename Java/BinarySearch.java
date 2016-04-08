/* This is a Class for Binary Search in java
   Written by Arpit Kumar Singh(13/CS/31)
   */


public class BinarySearch {
	
	public  static int   bsearch(int [] array,int size,int search){
		int lower_bound=0;//lower index
	    int higher_bound=size -1;//higher index
	    int index=-1;//index for search key
	    int mid=-1 ;//index for middle value 
		//while loop for comparison across the array
		while(lower_bound<=higher_bound){
			mid=(lower_bound+higher_bound)/2;
			if(array[mid]==search)
			{
				index=mid;
				break;
			}
			
			else if(array[mid]>search)higher_bound=mid-1;//element greater than middle element
			else lower_bound=mid+1;//element lower than the middle element
		}
		if(index!=-1)
		{    
			index+=1;
			return index;
		}
	else
	{  
		return -1;
	}
		
		
		
	}

}

