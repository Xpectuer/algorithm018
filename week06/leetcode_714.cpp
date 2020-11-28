class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int m = prices.size();
    
        int dp_i_0 = 0;
        int dp_i_1 = INT_MIN;
        for(int i = 0;i < m;i++) {
            int tmp = dp_i_0;
            dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
            dp_i_1 = max(dp_i_1, tmp- fee - prices[i]);
        }
        return dp_i_0;
        
        
    }
};

// dp[i][0] = max(dp[i-1][0], dp[i-1][1] - fee + prices[i])
// dp[i][1] = max(dp[i-1][1], dp[i-1][0]- fee + prices[i])
