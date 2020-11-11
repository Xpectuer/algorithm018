class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // Greedy
        if(prices.size() <= 1) return 0;

        int profit = 0;
        for(long long  i= 1,j=0; i< prices.size(); i++) {
            // buy
            if(prices[i] > prices[j]) {
                
                profit += prices[i] - prices[j];
                j = i;
            }
            else {
                j++;
            }
            

        }
        return profit;
    }
};
