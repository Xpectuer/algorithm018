class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }

    bool solve(vector<vector<char>>& board) {
         for(int i=0; i < board.size();i++) {
             for(int j=0; j < board[i].size();j++) {
                 if(board[i][j]=='.') {
                    for(char c = '1'; c <= '9'; c++) {
                        // trial 1-9
                        // cout<<"deadbeef"<<endl;
                        if(isValid(i,j,c,board)) {
                            board[i][j] = c;//put
                            if(solve(board))
                                return true;
                        //---------------------
                        // 第一个 "." 不能填
                            else
                                board[i][j] = '.';           
                        }
                       
                    } 
                    return false;
                 }
              
                 
             }
         }
        // i=0
        return true;
    }
    
private:
    bool isValid(int i, int j, char c, vector<vector<char> > &board) {
        for(int k=0; k < board.size(); k++) {
            //row
             if(board[i][k]!='.'&&board[i][k]==c) return false;
            //col
            if(board[k][j]!='.'&&board[k][j]==c) return false;
            //block
            if(board[3*(i/3)+k/3][3*(j/3)+k%3]!='.'&&
                board[3*(i/3)+k/3][3*(j/3)+k%3]==c) return false;
        }
        return true;
        
    }
};
