public class Solution {
    /**
     * @param A an integer array sorted in ascending order
     * @param target an integer
     * @return an integer
     */
  
    public int lastPosition(int[] A, int target) {
        // Write your code here
        int lenA = A.length;
        
        if(lenA == 0 || A == null || A[0] > target || A[lenA - 1] < target){
            return -1;
        }
        int start = 0, end = lenA - 1;
        while(start + 1< end){
            int mid = start + (end - start) / 2;
            if(A[mid] == target){
                start = mid ;
            }else if(A[mid] < target){
                start = mid ;
            }else{
                end = mid;
            }
        }
        if(A[end] == target){
            return end;
        }else if(A[start] == target){
            return start;
        }else{
            return -1;
        }
    }
}
