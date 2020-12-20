// dp 2 pointers compression
class Solution {
public:
    int trap(vector<int>& height) {
        if(height.size()<=2) return 0;
        int sum = 0;
        int max_left = 0;
        int max_right = 0;
        int left = 1;
        int right = height.size() - 2; // 加右指针进去
        
         for (int i = 1; i < height.size() - 1; i++) {
            //从左到右更
            if (height[left - 1] < height[right + 1]) {
                max_left = max(max_left, height[left - 1]);
                int min = max_left;
                if (min > height[left]) {
                    sum = sum + (min - height[left]);
                }
                left++;
            //从右到左更
            } else {
                max_right = max(max_right, height[right + 1]);
                int min = max_right;
                if (min > height[right]) {
                    sum = sum + (min - height[right]);
                }
                right--;
            }
        }
            return sum;
    }
};


