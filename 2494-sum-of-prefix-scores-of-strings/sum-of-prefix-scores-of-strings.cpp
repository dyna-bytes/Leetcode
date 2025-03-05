class Solution {
    class Trie {
        const int ROOT = 1;
        int unused;
#define MAX_LEN (1000 * 1000)
        unordered_map<int, int> end;;
        unordered_map<int, int> child[MAX_LEN];
        unordered_map<int, int> visited;

    public:
        void init() {
            unused = ROOT;
        }
        void insert(string& s) {
            int curr = ROOT;
            for (char c : s) {
                if (child[curr][c] == 0)
                    child[curr][c] = ++unused;
                curr = child[curr][c];
                visited[curr]++;
            }
            end[curr]++;
        }
        int find(string& s) {
            int curr = ROOT;
            int visited_sum = 0;

            for (char c : s) {
                if (child[curr][c] == 0)
                    return 0;
                curr = child[curr][c];
                visited_sum += visited[curr];
            }

            return visited_sum;
        }
    };

public:
    vector<int> sumPrefixScores(vector<string>& words) {
        Trie trie;
        trie.init();

        for (string& word : words)
            trie.insert(word);

        vector<int> scores(words.size());
        for (int i = 0; i < words.size(); i++) 
            scores[i] = trie.find(words[i]);
        
        return scores;
    }
};