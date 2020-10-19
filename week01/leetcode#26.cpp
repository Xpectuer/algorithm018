class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        vector<int> new_nums;
        int temp=INT_MIN;
        if(nums.size()==0)
            return 0;
        
        
        for(int i =0;i < nums.size();i++){
            
           if(temp != nums[i])
                new_nums.push_back(nums[i]);
        
            temp=nums[i];
        }
        nums = vector<int>(new_nums);
        return new_nums.size();
    }
};
