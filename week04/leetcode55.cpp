class Solution {
public:
    bool canJump(vector<int>& nums) {
        
        int k = 0;
        for(int i=0; i<= k; i++) {
            k = max(k, i+nums[i]);
            if(k>= nums.size() -1) return true;
        }
        return false;
    }
};
