class Solution {
    int bfs(string& beginWord, string& endWord, 
    unordered_map<string, unordered_set<string>>& adj) {
        queue<string> q;
        unordered_map<string, bool> visited;

        q.push(beginWord);
        visited[beginWord] = true;
        int step = 1;
        while (q.size()) {
            int qsize = q.size();
            while (qsize--) {
                string cur = q.front(); q.pop();
                if (cur == endWord) return step;

                for (const string& nxt: adj[cur]) {
                    if (visited[nxt]) continue;
                    visited[nxt] = true;
                    q.push(nxt);
                }
            }
            step++;
        }
        return 0;
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words(wordList.begin(), wordList.end());
        unordered_map<string, unordered_set<string>> adj;
        auto insertCloseWords = [&](const string& word) {
            for (int i = 0; i < word.size(); i++) {
                for (char c = 'a'; c <= 'z'; c++) {
                    string target = word.substr(0, i) + c + word.substr(i+1);
                    if (words.count(target)) {
                        adj[word].insert(target);
                        adj[target].insert(word);
                    }
                }
            }
        };

        insertCloseWords(beginWord);
        for (const string& word: words)
            insertCloseWords(word);
        
        return bfs(beginWord, endWord, adj);
    }
};