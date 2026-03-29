#define debug(x) cout << #x << " is " << x << endl;
class Solution {
    typedef pair<int, int> pii;
    int c1(int y, int x) {
        return x - y;
    }
    int c2(int y, int x) {
        return y + x;
    }
public:
    int visibleMountains(vector<vector<int>>& peaks) {
        for (auto& peak: peaks) {
            int x = peak[0], y = peak[1];
            peak = {c1(y, x), c2(y, x)};
        }
        sort(peaks.begin(), peaks.end(), [](auto& a, auto& b) {
            int lefta = a[0], righta = a[1];
            int leftb = b[0], rightb = b[1];
            if (lefta == leftb) return righta > rightb;
            return lefta < leftb;
        });

        int ret = 0;
        int max_right = 0;
        for (int i = 0; i < peaks.size(); i++) {
            vector<int>& peak = peaks[i];
            int left = peak[0], right = peak[1];
            if (right > max_right) {
                int nleft = -1, nright = -1;
                if (i + 1 < peaks.size()) {
                    vector<int>& nextPeak = peaks[i+1];
                    nleft = nextPeak[0];
                    nright = nextPeak[1];
                }

                max_right = right;
                if ((left == nleft) && (right == nright))
                    continue;
                ret++;
            }
        }

        return ret;
    }
};