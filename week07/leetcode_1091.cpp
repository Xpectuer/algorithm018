// TLE
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        // bfs
        if(grid.size()==0 || grid[0][0] || grid[grid.size()-1][grid.size()-1]) return -1;
        if(grid.size()<=2) return grid.size();
        
        deque<tuple<int, int, int> > q;
        q.push_back({0,0,1});
        vector<pair<int, int> > mov = {{0,1},{1,0},{1,1},{-1,-1},{-1,0},{0,-1},{1,-1},{-1,1}};
        int count=0;
        int n = grid.size();
        
        while(!q.empty()) {
                
            auto co = q.front();
            // reach the objective 
            // first reach must be the closest
            q.pop_front();
            // 8 direction tials
            for(auto p: mov) {
                int new_x = get<0>(co) + p.first;
                int new_y = get<1>(co) + p.second;
                if(new_x >= n || new_y >= n || new_x < 0 || new_y < 0 || grid[new_x][new_y] != 0)  continue;
                
                if(new_x==n-1&&new_y==n-1)  return get<2>(co) + 1;    
                q.push_back({new_x, new_y, get<2>(co)+1});
                // visited
                grid[get<0>(co)][get<1>(co)]== 1;    
            }
            
        }
        return -1;
        
        
    }
};
