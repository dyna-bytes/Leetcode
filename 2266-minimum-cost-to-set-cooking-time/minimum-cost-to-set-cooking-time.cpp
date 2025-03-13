class Solution {
public:
    int minCostSetTime(int startAt, int moveCost, int pushCost,
                       int targetSeconds) {
        auto cost = [&](char prev_num, int m, int s) {
            if (m < 0 || m > 99) return INT_MAX;
            if (s < 0 || s > 99) return INT_MAX;

            int res = 0;
            for (char num : to_string(m * 100 + s)) {
                res += (pushCost + (prev_num == num ? 0 : moveCost));
                prev_num = num;
            }
            return res;
        };

        int m = targetSeconds / 60, s = targetSeconds % 60;
        return min(cost(startAt + '0', m, s),
                   cost(startAt + '0', m - 1, s + 60));
    }
};