// Vanilla BFS
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict =unordered_set(wordList.begin(), wordList.end());
        // if target is not in dict
        if(!dict.count(endWord)) return 0;
        
        
        queue<string> q;
        q.push(beginWord);
        int l = beginWord.length();
        
        
        // unordered_set<string> q1{beginWord};
        // unordered_set<string> q2{endWord};
        
        int step = 0;
        
        while(!q.empty()) {
            ++step;
            for(int size = q.size(); size > 0; size--) {
                
                string w = q.front();
                q.pop();
                // visit all the chars in current word
                for(int i = 0;i<l;i++) {
                    // visit all the alphabet
                    char ch = w[i];
                    for(int j = 'a'; j <='z';j++) {
                        // change char in current word
                        w[i] = j;
                        // found solution
                        if(w == endWord) return step + 1;
                        // Not in dict , skip it
                        if(!dict.count(w)) continue;
                        // Remove new word from dict
                        // equal to visited[]
                        dict.erase(w);
                        //add new word into dict
                        q.push(w); 
                    }
                    w[i] = ch;
                }
            }
        }
        return 0;
    }
};
