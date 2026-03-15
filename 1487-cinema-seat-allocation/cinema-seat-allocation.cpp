class Solution {
    #define debug(x) cout << #x << " is " << x << endl;
    typedef bitset<10> B;
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        sort(reservedSeats.begin(), reservedSeats.end());
        vector<B> reserved;

        int i = -1;
        int prev_r = -1;
        for (vector<int>& seat: reservedSeats) {
            int r = seat[0], c = seat[1];
            if (prev_r != r) {
                reserved.push_back(B{}.flip());
                prev_r = r;
                i++;
            }
            reserved[i][10 - c] = false;
        }

        B mask_left = 0xF << 5;
        B mask_right = 0xF << 1;
        B mask_mid = 0xF << 3;
        int ret = 0;
        for (B& seat: reserved) {
            if ((seat & mask_left) == mask_left) {
                ret++;

                if ((seat & mask_right) == mask_right)
                    ret++;
            } else if ((seat & mask_mid) == mask_mid)
                ret++;
            else if ((seat & mask_right) == mask_right)
                ret++;
        }
        return ret + 2*(n - reserved.size());
    }
};