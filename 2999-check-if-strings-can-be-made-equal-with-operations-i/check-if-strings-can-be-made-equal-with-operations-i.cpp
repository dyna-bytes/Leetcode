class Solution {
public:
    bool canBeEqual(string s1, string s2) {
        for (int i = 0; i < 4; i++) {
            char c = s1[i];
            int j = (i + 2) % 4;

            if (s2[i] == c || s2[j] == c) continue;
            return false;
        }
        return true;
    }
};