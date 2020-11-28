class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
       
        if(amount==0 || coins.size()==0) return 0;
        // base case: dp[i] = inf
        vector<int> dp(amount+1  , amount + 1);
        // base case: 0 0
        dp[0] = 0;
        for(int i = 0; i < amount + 1; i++) {
            for(int j=0;j < coins.size();j++) {
                if(i >= coins[j])
                dp[i] = min(dp[i], dp[i-coins[j]]+1); 
            }
        }
        return dp[amount] > amount?-1: dp[amount];
        
    }
};
// a. subproblem: min(f(n-k), for k in [a,b,c]) + 1
//        
//    base case: 0  n = amount
// b. state: which denomination to use ?
// c. dp[i] = min(dp[i -1][j][],dp[i-1][j][])
