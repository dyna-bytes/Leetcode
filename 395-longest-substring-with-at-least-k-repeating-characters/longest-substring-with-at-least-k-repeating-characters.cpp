class Solution {
    #define debug(x) cout << #x << " is " << x << endl;
public:
    int longestSubstring(string str, int k) {
        auto unique = [&](int w) {
            int ret = 0;
            unordered_map<char, int> exists;
            for (int s = 0, e = 0; e < str.size(); ) {
                exists[str[e++]]++;
                while (exists.size() > w) {
                    if (--exists[str[s++]] == 0)
                        exists.erase(str[s - 1]);
                }

                int ok = exists.size() == w;
                for (auto& [c, freq]: exists) {
                    if (freq < k) {
                        ok = false;
                        break;
                    }
                }

                if (ok)
                    ret = max(ret, e - s);
            }
            return ret;
        };

        int ret = 0;
        for (int w = 1; w <= 26; w++)
            ret = max(ret, unique(w));
        return ret;
    }
};