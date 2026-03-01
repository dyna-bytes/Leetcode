class Solution {
    int ctoi(char c) {
        return c - '0';
    }
public:
    int minPartitions(string n) {
        int res = 0;
        int max_x = 0;
        for (int i = 0; i < n.size(); ++i) {
            int x = ctoi(n[i]);
            res += max(0, x - max_x);
            max_x = max(max_x, x);
        }
        return res;
    }
};