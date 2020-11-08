class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};
        unordered_map<char, string> phoneMap{
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}
        };
        vector<string> ans;
    
         _generate("", 0,digits, phoneMap,ans);

         return ans;
    }
    
    void _generate(string s,
        long long i,
    const string digits,
    const unordered_map<char, string> phoneMap ,
     vector<string> &ans) {
        if(i==digits.size()) {
            ans.push_back(s);
            return;
        }

        const string &letters= phoneMap.at(digits[i]);
        for(auto &c: letters) {
            // drill down
            
            _generate(s+c, i+1,digits,phoneMap, ans);
            
        
        }

        //reverse
        


    }
    
};
