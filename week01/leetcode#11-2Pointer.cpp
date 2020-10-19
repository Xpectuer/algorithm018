class Solution {
public:


    int maxArea(vector<int>& height) {       
        // double pointer
        int l=0,r=height.size()-1;
        int area=0;
        int maxArea = (r-l)*min(height[l],height[r]) ;
        while(l<r){
            if(height[l]>height[r])
                r--;
            else
                l++;
            area = (r-l)*min(height[l],height[r]);
            maxArea = max( area, maxArea);
        }
        return maxArea;

    }
};
