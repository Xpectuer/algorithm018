class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        long long n = nums.size();
        if(n==0) return {};
        
        // dfs
        
        vector<vector<int> > rs; 
        vector<int> path;   
        dfs(0, n, nums, path, rs);
        
        
        return rs;
        
    }
    
    
    void dfs(int i,  int n, const vector<int> nums, vector<int> &path, vector<vector<int> > &rs) {
        
        if(i==n) {
            rs.push_back(path);
            return;
        }
        
        
        for(int j=0; j<= path.size(); j++) {
            path.insert(path.begin()+j, nums[i]);
            dfs(i+1, n, nums, path, rs);
            path.erase(path.begin() + j);
            
        }
        
    }
};
