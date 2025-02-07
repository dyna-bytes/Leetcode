class Solution {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        int N = reward1.size();
        vector<pair<int, int>> diff(N);
        for (int i = 0; i < N; i++) {
            diff[i] = {reward1[i] - reward2[i], i};
        }

        sort(diff.begin(), diff.end(), [&](auto l, auto r) {
            return l.first > r.first;
        });

        int ans = 0;
        for (int i = 0; i < k; i++)
            ans += reward1[diff[i].second];
        for (int i = k; i < N; i++)
            ans += reward2[diff[i].second];
        return ans;
    }
};