class Solution {
private:
    vector<string> rs;
public:
    vector<string> generateParenthesis(int n) {
        if(n==0) return {};
        _generate(0, 0, n, "");
        return rs;
    }

    void _generate(int left, int right, int n, string brace) {
        if(left==n && right==n) {
            rs.push_back(brace);
            return;
        }

        if(left < n) _generate(left+1, right,n, brace+"(");
        if(left > right) _generate(left,right+1,n,brace+")");
    }
};
