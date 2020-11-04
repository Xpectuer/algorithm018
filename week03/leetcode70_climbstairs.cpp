class Solution {
public:
    int climbStairs(int n) {
        int a = 1,b=1,c=1;
        // slide pointer
        while(--n){
            c= a +b;
            a=b;
            b=c;
        }
        return c;
    
    }

};

