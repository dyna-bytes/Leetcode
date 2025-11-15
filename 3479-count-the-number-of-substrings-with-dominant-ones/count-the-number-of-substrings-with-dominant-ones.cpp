/*
 * for (0 <= l < n) 
 *  for (0 <= k <= sqrt(n))
 *      r_begin = r s.t. count_lr(0) = k
 *      r_end = r s.t. count_lr(0) = k+1
 *      r_lowerbound = l + k^2 + k - 1 // count_lr(1) = (r - l + 1) - k >= count_lr(0)^2
 *      r_min = max(r_begin, r_lowerbound)
 *      ans += (r_end - r_min)
 *
*/
#define debug(x) cout << #x << " is " << x << endl;
class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.size();
        int ans = 0;
        vector<int> pre(n+1, 0); // pre[k+1] : position of nearest 0 before position k

        pre[0] = -1;
        for (int i = 0; i < n; i++)
            if (i == 0 || (i > 0 && s[i - 1] == '0'))
                pre[i + 1] = i;
            else
                pre[i + 1] = pre[i];

        for (int r = 1; r <= n; r++) {
            int cnt0 = s[r - 1] == '0';
            for (int l = r; l > 0 && cnt0 * cnt0 <= n; l = pre[l]) {
                int cnt1 = (r - pre[l]) - cnt0;
                if (cnt0 * cnt0 <= cnt1)
                    ans += min(l - pre[l], cnt1 - cnt0 * cnt0 + 1);
                cnt0++;
            } 
        }

        return ans;
    }
};