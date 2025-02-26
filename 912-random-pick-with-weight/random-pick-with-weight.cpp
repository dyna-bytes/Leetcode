class Solution {
public:
    vector<int> prefix_sum; // prefix_sum[n] = w[0] + ... w[n-1]
    Solution(vector<int>& w) {
        prefix_sum.resize(w.size()+1, 0);
        for (int i = 1; i < w.size()+1; i++) {
            prefix_sum[i] = prefix_sum[i-1] + w[i-1];
        }
    }
    
    int pickIndex() {
        int val = rand() % prefix_sum.back();

        int l = 0, r = prefix_sum.size() - 1;
        while (l + 1 < r) {
            int m = (l + r)/2;
            if (val < prefix_sum[m])
                r = m;
            else
                l = m;
        }
        return l;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */