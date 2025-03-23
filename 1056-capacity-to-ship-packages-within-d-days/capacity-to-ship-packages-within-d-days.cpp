class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int l = 0;
        int r = 0;
        for (int w: weights) r += w;

        while (l + 1 < r) {
            int m = (l + r)/2;
            if (possible(m, weights, days)) r = m;
            else l = m;
        }
        return l + 1;
    }
    bool possible(int capacity, vector<int>& weights, int days) {
        int day = 0;
        int sum = 0;
        for (int i = 0; i < weights.size(); day++) {
            if (day > days) return false;

            while (i < weights.size() && sum + weights[i] <= capacity) {
                sum += weights[i];
                i++;
            }
            sum = 0;
        }
        return day <= days;
    }
};