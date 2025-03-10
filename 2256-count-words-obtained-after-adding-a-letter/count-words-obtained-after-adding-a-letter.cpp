class Solution {
public:
    int stringToBits(string& word) {
        int ret = 0;
        for (char c : word) {
            int x = c - 'a';
            ret |= (1 << x);
        }
        return ret;
    }
    int numBits(int bit) {
        int ret = 0;
        for (int i = 0; i < 27; i++)
            if ((1 << i) & bit)
                ret++;
        return ret;
    }

    int wordCount(vector<string>& startWords, vector<string>& targetWords) {
        vector<unordered_set<int>> starts(27);
        vector<multiset<int>> targets(27);

        for (string& word : startWords) {
            int bit = stringToBits(word);
            starts[word.size()].insert(bit);
        }

        for (string& word : targetWords) {
            int bit = stringToBits(word);
            targets[word.size()].insert(bit);
        }

        int ans = 0;
        for (int bitSize = 1; bitSize <= 26; bitSize++)
            for (int targetBit : targets[bitSize])
                for (int b = 0; b <= 26; b++)
                    if ((1 << b) & targetBit) {
                        if (starts[bitSize - 1].count(targetBit & ~(1 << b))) {
                            ans++;
                            break;
                        }
                    }
                
        return ans;
    }
};