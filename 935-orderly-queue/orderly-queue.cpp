class Solution {
public:
    string orderlyQueue(string s, int k) {
        int N = s.size();
        if (k == 1) {
            string min_s = s;
            for (int i = 0; i < N; i++) {
                rotate(s.begin(), next(s.begin()), s.end());
                min_s = min(min_s, s);
            }
            return min_s;
        }

        sort(s.begin(), s.end());
        return s;
    }
};