class Solution {
    vector<string> words;
    unordered_map<char, int> dict;
    vector<int> score;
public:
    bool canUse(string& word) {
        for (char c: word) 
            if (!dict[c]) return false;
        return true;
    }
    int use(string& word) {
        int s = 0;
        for (int i = 0; i < word.size(); i++) {
            char c = word[i];
            if (--dict[c] < 0) {
                for (int ii = i; ii >= 0; ii--)
                    ++dict[word[ii]];
                return 0;
            }
            s += score[c - 'a'];
        }
        return s;
    }
    void reset(string& word) {
        for (char c: word)
            dict[c]++;
    }
    int getMax(int curr) {
        if (curr == words.size()) return 0;
        int ret = 0;
        int sc = use(words[curr]);
        if (sc) {
            ret += (sc + getMax(curr + 1));
            reset(words[curr]);
        }
        ret = max(ret, getMax(curr + 1));
        return ret;
    }
    int maxScoreWords(vector<string>& words, vector<char>& letters,
                      vector<int>& score) {
        this->words = words;
        this->score = score;

        for (auto letter: letters)
            dict[letter]++;

        return getMax(0);
    }
};