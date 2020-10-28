/*
 * @Author: your name
 * @Date: 2020-10-28 14:22:09
 * @LastEditTime: 2020-10-28 14:34:39
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /undefined/Users/alex/.leetcode/242.有效的字母异位词.cpp
 */
/*
 * @lc app=leetcode.cn id=242 lang=cpp
 *
 * [242] 有效的字母异位词
 */

// @lc code=start
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size() != t.size()) return false;

        vector<char> alphabet(26);
        
        for(size_t i=0;i<t.size();i++) {
            alphabet[s[i]-'a']++;
            alphabet
            [t[i]-'a']--;
        }

        for(int i:alphabet){
            if(i!=0)
                return false;
        }
        return true;
        
    }
};
// @lc code=end


