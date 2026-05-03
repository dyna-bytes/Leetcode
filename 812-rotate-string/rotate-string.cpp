class Solution {
public:
    bool rotateString(string s, string goal) {
        if (s.size() != goal.size()) return false;
        
        for (int i = 0; i < s.size(); i++) {
            int matched = true;
            for (int j = i; j < i + s.size(); j++) {
                int sidx = j % s.size();
                int gidx = (j - i);

                if (s[sidx] != goal[gidx]) {
                    matched = false;
                    break;
                }
            }

            if (matched)
                return true;
        }
        return false;
    }
};