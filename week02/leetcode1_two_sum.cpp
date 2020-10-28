class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
        // single time hashmap
        int n = nums.size();
        
        if(n==0) {
            return {};
        }
        // map

        unordered_map<int,int>  map;
        // initialize the map
        for(int i= 0;i <n ;i++) {
            auto it = map.find(target-nums[i]);
            if(it!=map.end()) return {i,it->second};
            map.emplace(nums[i],i);
        }

        return {};
    }
  
    
};
