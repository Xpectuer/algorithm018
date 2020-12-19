class Solution {
public:
    int myAtoi(string s) {
        if(s.length()==0) return 0;
        int index =0,n=s.length();
        // trim without extra space
        while(index<n && s[index]==' ') index++;
        cout<<"index: "<<index<<endl;
        // sign negative or positive
        int sign =1;//1 or -1
        if(s[index]=='-') {
            sign = -1;
            index++;
        } else if(s[index]=='+') {
            index++;
        }
        // extra char
        int end = index;
        while(end<n&&s[end]>='0'&&s[end]<='9') end++;
        cout<<"end: "<<end<<endl;
        // covert
        int total = 0;
        // k : pos of num
        while(index < s.length()) {
            int digit = s[index]-'0';
            if(digit < 0 || digit >9) break;
            if(INT_MAX/10 < total ||
              INT_MAX/10 == total && INT_MAX %10 <digit) 
                return sign==1?INT_MAX:INT_MIN;
            total = 10 * total + digit;
            index ++;
        }
        return total * sign;
        
        
    }
};
