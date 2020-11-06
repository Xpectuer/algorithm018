class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        if(nums.size()==0) return {};
        vector<int> list;
        vector<vector<int>> ans;
        dfs(0, nums, list, ans,nums.size());
        return ans;
    }
    void dfs(int i,const vector<int> nums,vector<int> list, vector<vector<int>> &ans, int n) {
        if(i==n) {
            ans.push_back(list);
            return;
        }
        
        // do not select
        dfs(i+1, nums, list, ans, n);
        // select
        list.push_back(nums[i]);
        dfs(i+1, nums, list, ans, n);
       

    }
};
