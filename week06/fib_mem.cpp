class Solution {
public:
    int fib(int N) {
        vector<int> mem(N+1);
        fill(mem.begin(), mem.end(),0);
        return fib(N, mem);
        
    }
    int fib(int N, vector<int> &mem) {
        
        if(N <= 0) {
            return 0;
        }
        else if(N==1) {
            return 1;
        }
        else if(mem[N]==0) {
            mem[N] = fib(N - 1, mem)+ fib(N - 2,mem); 
        }
        return mem[N];

    }
};
