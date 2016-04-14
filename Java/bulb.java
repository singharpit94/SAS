import java.util.*;
public class Bulbs {
    public static int bulbs(ArrayList<Integer> A) {
        
        int switchCount = 0;
        for(int i = 0; i < A.size(); i++) {
            if(A.get(i) == 0){
                switchCount++;
                for(int j = i; j < A.size(); j++) {
                    if(A.get(j) == 0){
                        A.set(j, 1);
                    }
                    else {
                        A.set(j, 0);
                    }
                }
            }
        }
        return switchCount;
    }
