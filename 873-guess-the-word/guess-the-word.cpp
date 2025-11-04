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
    typedef pair<int, int> pii;

    int guess(string& u, string& v) {
        int res = 0;
        for (int i = 0; i < u.size(); i++)
            res += (u[i] == v[i]);
        return res;
    }
public:
    void findSecretWord(vector<string>& words, Master& master) {
        random_shuffle(words.begin(), words.end());
        for (int i = 0, score = 0; i < 30 && score != 6; i++) {
            string& test = words[0]; //words[rand() % words.size()];
            score = master.guess(test);

            vector<string> candidates;
            for (string& word: words)
                if (score == guess(test, word))
                    candidates.push_back(word);
            words = candidates;
        }
    }
};