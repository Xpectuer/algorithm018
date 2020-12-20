// TLE 
class Solution {
public:
    int trap(vector<int>& height) {
        if(height.size()<=2) return 0;
         int ret = 0;
        for(int i = 1;i < height.size()-1;i++) {
            
            int max_left = 0;
            for(int j = i-1; j >= 0; i--) {
                if(height[j] > max_left) max_left = height[j];
            }
            int max_right =0;
            for(int j = i+ 1;j<height.size();j++) {
                if(height[j] > max_right) max_right =height[j];
            }
            
            int max_bound = min(max_left, max_right);
            
            if(max_bound > height[i]) {
                ret = ret + (max_bound - height[i]);
            }
        
        }
        return ret;
        
    }
};
