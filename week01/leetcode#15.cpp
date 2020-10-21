class Solution {
public:
    vector<vector<int> > threeSum(vector<int>& nums) {
        
        
        unsigned int n= nums.size();
        
        sort(nums.begin(),nums.end());
        
        vector<vector<int> > numss;
        
        
        
        int i =1,j =n-1;
        int rs = 0;
        for(unsigned int k = 0; k<n; k++) {
            
            if(nums[k]>0) return numss;
            
            int i = k+1, j = n - 1;
            
            while( i < j ){
                
                rs = nums[k]+nums[i]+nums[j];
                
                if( rs < 0 ) {
                        i++;
                }


                else if( rs > 0 ) {
                        j--;
                }
                
                else{
                    // delete  duplicated results 
                    vector<int> triplet(3,0);
                    triplet[0] = nums[k];
                    triplet[1] = nums[i];
                    triplet[2] = nums[j];
                    
                    
                    numss.push_back(triplet);
                  
                    
                    // Processing duplicates of Number 2
                    while (i < j && nums[i] == triplet[1] ) i++;
                    // Processing duplicates of Number 3
                    while (i < j && nums[j] == triplet[2] ) j--;
                   
                }
                
            
            }
            //  Processing duplicates of Number 1

             while (k + 1 < nums.size() && nums[k + 1] == nums[k]) 
                 k++;
          
        }
        
        return numss;
        
    }
};
