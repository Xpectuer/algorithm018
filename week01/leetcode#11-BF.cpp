class Solution {
public:
    // out of time

    int maxArea(vector<int>& height) {       
         //Brute Force

        int maxArea=0;

        for(int i=0; i < height.size();i++){
            for(int j=i+1;j < height.size();j++){
                maxArea = max(  maxArea, min(height[i],height[j])*(j-i) );
            }
        }

        return maxArea;



    }
};
