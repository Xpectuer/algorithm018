学习笔记

## 高级动态规划



不同路径II dp 方程
$$
dp[i][j] = 
\begin{cases}
dp[i-1][j] + dp[i][j-1],\ grid[i][j]=0\\
\\
0,\ grid[i][j]=1
\end{cases}
$$

```cpp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        if(m==0||n==0||obstacleGrid[0][0]==1||obstacleGrid[m-1][n-1]==1)            return 0;
        
        vector<vector<int> > dp(m, vector<int>(n,0));
         for(int i=0;i<m&&obstacleGrid[i][0]==0;i++) {
            dp[i][0] = 1;
        }
         for(int j=0;j<n&&obstacleGrid[0][j]==0;j++) {
            dp[0][j] = 1;
        }
        
        for(int i=1;i<m;i++) {
            for(int j=1;j<n;j++) {
                if(obstacleGrid[i][j]==0){
                    dp[i][j] = dp[i-1][j]+dp[i][j-1];    
                }
                else {
                    dp[i][j] =0;
                }
                
            }
        }
        return dp[m-1][n-1];
    }
};
```

### 最短路径

```cpp
class Solution {
private:
    vector<vector<int> > memo;
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        
        vector<vector<int> > dp(grid);
        dp[0][0] = grid[0][0];
        for(int i=0;i<m;i++) {
            for(int j=0;j<n;j++) {
                if(i==0&&j==0) continue;
                else if(j==0) dp[i][j] = dp[i-1][j] + grid[i][j];
                else if(i==0) dp[i][j] = dp[i][j-1] + grid[i][j];
                else dp[i][j] = min(dp[i-1][j],dp[i][j-1]) + grid[i][j];
            }    
        }      
        return dp[m-1][n-1];
    }
};
```

### 编辑距离

```cpp
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
```

