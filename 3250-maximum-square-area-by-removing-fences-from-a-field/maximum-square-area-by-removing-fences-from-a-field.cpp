class Solution {
    const int mod = 1e9 + 7;
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        hFences.push_back(1);
        hFences.push_back(m);
        sort(hFences.begin(), hFences.end());

        vFences.push_back(1);
        vFences.push_back(n);
        sort(vFences.begin(), vFences.end());

        unordered_map<int, int> seen;
        for (int i = 0; i < hFences.size(); i++) {
            for (int j = i + 1; j < hFences.size(); j++) {
                int diff = hFences[j] - hFences[i];
                seen[diff] = true;
            }
        }

        int max_common = -1;
        for (int i = 0; i < vFences.size(); i++) {
            for (int j = i + 1; j < vFences.size(); j++) {
                int diff = vFences[j] - vFences[i];
                if (seen[diff])
                    max_common = max(max_common, diff);
            }
        }

        if (max_common == -1)
            return -1;

        return 1LL * max_common * max_common % mod;
    }
};