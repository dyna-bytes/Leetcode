class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, vector<int>> um;
        for (int i = 0; i < n; i++) {
            um[nums[i]].push_back(i);
        }

        int mindist = INT_MAX;
        for (auto& [num, vc]: um) {
            if (vc.size() < 3) continue;

            int i, j, k;
            int qsize = 0;
            for (int idx: vc) {
                qsize++;
                i = j, j = k, k = idx;
                if (qsize == 3) {
                    int dist = abs(i - j) + abs(j - k) + abs(k - i);
                    mindist = min(mindist, dist);
                    qsize--;
                }
            }
        }

        if (mindist == INT_MAX) return -1;
        return mindist;
    }
};