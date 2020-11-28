class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<int> dp(n+1,0);
        dp[0] = 1;
        dp[1] = s[0]!='0'?1:0;
        for(int i=2;i <= n; i++) {
            int way1=0, way2=0;
            if(s[i-1]!='0') way1 = dp[i-1];
           
            if(stoi(s.substr(i-2,2)) <=26&&stoi(s.substr(i-2,2))>0&&s[i-2]!='0') way2 = dp[i-2];
           
            dp[i] = way1 + way2;
        }
        return dp[n];
    }
   
};
// status: 1 step 2 step
