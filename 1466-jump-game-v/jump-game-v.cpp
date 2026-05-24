class Solution {
    vector<int> arr;
    int d;
    int n;
    vector<int> dp;
    int f(int i) {
        int& ret = dp[i];
        if (ret != -1) return ret;
        ret = 0;

        int l = i;
        for (int x = i-1; x >= max(0, i-d); x--) {
            if (arr[x] >= arr[i]) break;
            l = x;
        }
        int r = i;
        for (int x = i+1; x <= min(n-1, i+d); x++) {
            if (arr[x] >= arr[i]) break;
            r = x;
        }

        for (int x = l; x <= r; x++) {
            if (x == i) continue;
            ret = max(ret, f(x));
        }

        return ++ret;
    }

public:
    int maxJumps(vector<int>& arr, int d) {
        this->arr = arr;
        this->d = d;
        this->n = arr.size();
        dp.assign(n, -1);

        int ret = 0;
        for (int i = 0; i < n; i++)
            ret = max(ret, f(i));
        return ret;
    }
};