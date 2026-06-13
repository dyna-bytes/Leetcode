class Solution {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        string ret;
        for (string& word: words) {
            int weight_sum = 0;
            for (char c: word) {
                int n = c - 'a';
                weight_sum += weights[n];
            }
            weight_sum %= 26;
            char ch = 'z' - weight_sum;
            ret.push_back(ch);
        }
        return ret;
    }
};