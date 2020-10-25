class Solution {
public:
    bool isValid(string s) {
       int n = s.length(); 
    

        if(n % 2 == 1){
            return false;
        }

        unordered_map <char,char> pair = unordered_map<char,char>{
            {'}','{'},
            {')','('},
            {']','['}
        };

         stack<char> str_stk;
        for(char c : s) {
            // check stack
            
                    if( pair.count(c) ) {
                         if( str_stk.empty() || str_stk.top() != pair[ c ]) {
                            return false;
                        }
                        str_stk.pop();
                    }
                    
                    // unpairable
                   
                    else {
                        str_stk.push(c);
                    }

                }
                
            
             return str_stk.empty();
        }
       
    

};
