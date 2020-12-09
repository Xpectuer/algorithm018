class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> cnt;
        int count;
        for(uint32_t i=0; i<=num; i++) {
            count =0;
            cout << i << endl;
            uint32_t mid = i;
            while(mid!=0 ) {
                count++;
                mid = mid&(mid-1);
            }
            
            cnt.push_back(count);
        }
        return cnt;
    }
};
