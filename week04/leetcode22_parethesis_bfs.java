class Solution {
    public List<String> generateParenthesis(int n) {
        Queue<String> strQ = new LinkedList<>();
        Queue<Integer> leftQ = new LinkedList<>();
        Queue<Integer> rightQ = new LinkedList<>();
        
        strQ.offer("");
        leftQ.offer(0);
        rightQ.offer(0);
        
        while(leftQ.peek() + rightQ.peek() < n * 2) {
            
            int size = strQ.size();
            
            while(size -- > 0) { 
                String cur = strQ.poll();
                int left = leftQ.poll();
                int right = rightQ.poll();
                
                if(left < n) {
                    strQ.offer(cur + "(");
                    leftQ.offer(left +1);
                    rightQ.offer(right);
                }
                
                if(left > right) {
                    strQ.offer(cur +")");
                    leftQ.offer(left);
                    rightQ.offer(right + 1);
                }
                
            }
        }
        return (List<String>) strQ;
        
    }
}
