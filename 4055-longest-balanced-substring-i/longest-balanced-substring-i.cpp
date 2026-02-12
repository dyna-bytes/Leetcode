class Solution {
    vector<vector<int>> freq; // prefix sum of frequency per alphabet by index
    // freq[i][c] = [0, i) 까지 c 의 등장 횟수
    // freq[e][c] - freq[s][c] = [s, e) 까지 c 의 등장 횟수
    bool isBalanced(int start, int end) {
        int prev_f = -1;
        for (int c = 0; c < 26; c++) {
            int f = freq[end][c] - freq[start][c];
            if (f == 0) continue;
            if (prev_f == -1) prev_f = f;
            if (prev_f != f) return false;
        }
        return true;
    }
public:
    int longestBalanced(string s) {
        int n = s.size();
        freq.resize(n + 1, vector<int>(26, 0));

        for (int i = 1; i <= n; i++) {
            int curr = s[i-1] - 'a';
            for (int j = 0; j < 26; j++)
                freq[i][j] = freq[i-1][j] + (curr == j);
        }

        int lbs = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (isBalanced(i, j))
                    lbs = max(lbs, j - i);
            }
        }
        return lbs;
    }
};