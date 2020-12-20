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



## 字符串算法



### 大小写转换

奇技淫巧

```cpp
 /* 位运算（解题区的思路
        大写变小写、小写变大写 : 字符 ^= 32;
        大写变小写、小写变小写 : 字符 |= 32;  
        小写变大写、大写变大写 : 字符 &= -33;
        eg：
        65(A)->二进制表示为100 0001
        32的二进制表示为 010 0000 
        100 0001|010 0000=110 0001->97(a)
        */

        for(auto& s:str)
            s|=32;
        return str;
```

### 最后一个单词的长度

```cpp
class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = s.length()-1;
        while(s[n]==' ') n--;
        if(n<0) return 0;
        // 再来一个指针
        int start = n;
        for(;start>=0&&s[start]!=' ';start--){}
        return n-start;
    }
};
```



#### atoi

```cpp
class Solution {
public:
    int myAtoi(string s) {
        if(s.length()==0) return 0;
        int index =0,n=s.length();
        // trim without extra space
        while(index<n && s[index]==' ') index++;
        cout<<"index: "<<index<<endl;
        // sign negative or positive
        int sign =1;//1 or -1
        if(s[index]=='-') {
            sign = -1;
            index++;
        } else if(s[index]=='+') {
            index++;
        }
        // extra char
        int end = index;
        while(end<n&&s[end]>='0'&&s[end]<='9') end++;
        cout<<"end: "<<end<<endl;
        // covert
        int total = 0;
        // k : pos of num
        while(index < s.length()) {
            int digit = s[index]-'0';
            if(digit < 0 || digit >9) break;
            if(INT_MAX/10 < total ||
              INT_MAX/10 == total && INT_MAX %10 <digit) 
                return sign==1?INT_MAX:INT_MIN;
            total = 10 * total + digit;
            index ++;
        }
        return total * sign;
        
        
    }
};
```



### 字母异位词分组

1. 排序每个单词作为key，识别模式
2. 存入map中
   1. 已存在模式，加入已有的模式中
   2. 对于不存在的模式，增加新模式

```java
class Solution {
    public List<List<String>> groupAnagrams(String[] strs) {
        Map<String, List<String>> map = new HashMap<String, List<String>>();
        for(String s: strs) {
            char [] array = s.toCharArray();
          // 排序key
            Arrays.sort(array);
            String key = new String(array);
          // 
             List<String> list = map.getOrDefault(key, new ArrayList<String>());
            list.add(s);
            map.put(key, list);
        }
        return new ArrayList<List<String>>(map.values());
    }
}
```

![「动态规划」问题思考方向.png](/Users/alex/Library/Mobile Documents/com~apple~CloudDocs/CSDN/blogs/Algo/1f95da43d1bdeebdd1213bb804034ddc5f906dc61451cd63f2b5ab5d0eb33b33-「动态规划」问题思考方向.png)

### 最大回文子串

```java
// 中心向外扩展
//O(N+N-1)
public class Solution {
private int lo, maxLen;

public String longestPalindrome(String s) {
	int len = s.length();
	if (len < 2)
		return s;
	
    for (int i = 0; i < len-1; i++) {
     	extendPalindrome(s, i, i);  //assume odd length, try to extend Palindrome as possible
     	extendPalindrome(s, i, i+1); //assume even length.
    }
    return s.substring(lo, lo + maxLen);
}

private void extendPalindrome(String s, int j, int k) {
	while (j >= 0 && k < s.length() && s.charAt(j) == s.charAt(k)) {
		j--;
		k++;
	}
	if (maxLen < k - j - 1) {
		lo = j + 1;
		maxLen = k - j - 1;
	}
}}
```

