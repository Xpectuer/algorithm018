class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length(), n = word2.length();
        if(m==0||n==0) return m==0 ? n : m;
        vector<vector<int> > dp(m+1, vector<int>(n+1,0));
        
        for(int i=0;i<=m;i++) 
            dp[i][0] = i;
        for(int j=0;j<=n;j++)
            dp[0][j] = j;
        
        for(int i = 1;i<=m;i++) {
            for(int j=1;j<=n;j++) {
                if(word1[i-1]==word2[j-1]) 
                    dp[i][j] = dp[i-1][j-1];
                else
                    dp[i][j] = min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]) + 1;
            }
        }
        
        // for(auto &i:dp) {
        //     cout<<endl;
        //     for(auto j:i) {
        //         cout<<j<<" ";
        //     }
        // }
        return dp[m][n];
    }
    
    int min(int a,int b, int c) {
        if(a>b){
            return b>=c?c:b;
        }
        else{
            return a>=c?c:a;
        }
        
    }
};
