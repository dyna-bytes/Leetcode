#define DBG
#ifdef DBG
#define debug(x) cout << #x << " is " << x << endl;
#else
#define debug(x)
#endif

/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
    int guess(string& u, string& v) {
        int res = 0;
        for (int i = 0; i < u.size(); i++)
            res += (u[i] == v[i]);
        return res;
    }
public:
    void findSecretWord(vector<string>& words, Master& master) {
        for (int i = 0; i < 30; i++) {
            random_shuffle(words.begin(), words.end());

            map<int, string> penalties;
            unordered_map<string, vector<vector<string>>> bucket_group;
            for (string& word: words) {
                bucket_group[word].assign(7, vector<string>());
                vector<vector<string>>& buckets = bucket_group[word];

                for (string& other: words) {
                    if (word == other) continue;
                    int score = guess(word, other);
                    buckets[score].push_back(other);
                }

                ulong max_sz = 0;
                for (vector<string>& bucket: buckets)
                    max_sz = max(max_sz, bucket.size());

                penalties[max_sz] = word;
            }

            string target = penalties.begin()->second;
            int score = master.guess(target);
            if (score == 6) break;

            words = bucket_group[target][score];
        }
    }
};