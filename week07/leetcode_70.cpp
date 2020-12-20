class Solution {
private: 
    
public:
    int climbStairs(int n) {
        if(n<=2) return n;
        vector<int> memo(n+1, 0);
        //  n > 2
        return climbStairs(n, memo);
    }
    int climbStairs(int n,vector<int> &memo) {
        if(n<=2) {
            memo[n] = n;
            return n;
        }
        if(memo[n]==0) {
            memo[n] = climbStairs(n-1, memo) + climbStairs(n-2, memo);
        }
        cout << 111<<endl;
        return memo[n];
            
    }
};
