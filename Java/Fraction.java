import java.util.*;
public class Fraction{
    public static String fractionToDecimal(int n, int de) {
        if(n == 0)
            return "0";
        if(de == 0)
            return "";
        HashMap<Long, Integer> map = new HashMap<Long, Integer>();
        String tempResult = "";
        String result = "";
        if ((n < 0) && (de > 0) || (n > 0) && (de < 0)) {
            result += "-";
        }
        long numerator = n;
        long denominator = de;
       numerator = Math.abs(numerator);
        denominator = Math.abs(denominator);
        System.out.println("numerator : " + numerator);
        System.out.println("denominator : " + denominator);
        long res = numerator/denominator;
        result += String.valueOf(res);
        
        long remainder = (numerator % denominator) * 10;
        System.out.println("remainder after calculating before . part: " + remainder);
        if(remainder == 0)
            return result;
        
        result += '.';
        
        while(remainder != 0){
            System.out.println("remainder : " + remainder);
            if(map.containsKey(remainder)){
                int beg = map.get(remainder);
                String part1 = result.substring(0, beg);
                String part2 = result.substring(beg, result.length());
                result = part1 + "(" + part2 + ")";
                return result;
            }
            map.put(remainder, result.length());
            res = remainder/denominator;
            result += String.valueOf(res);
            remainder = (remainder % denominator) * 10;
        }
        
        
        
        return result;
        
    }
