class Solution {
public:
    string reverseWords(string s) 
    {
        stack<string> stk;
        string res, temp;
        // ss 可以空格为界分开，可以不考虑
        istringstream ss(s); // ss与数输入的字符串s绑定
        while (ss >> temp)   // 以空格为分隔符将其分割
        {
            stk.push(temp);
            stk.push(" ");
        }
        if(!stk.empty()) 
            stk.pop();       // 弹出最后压入的那个多余空格
        while (! stk.empty())// 单词翻转后的新串
        {
            res += stk.top();
            stk.pop();
        }
        return res;
    }
};

