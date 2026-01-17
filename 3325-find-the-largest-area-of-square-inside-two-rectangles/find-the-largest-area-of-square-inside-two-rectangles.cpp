#define debug(x) cout << #x << " is " << x << endl;

class Solution {
    typedef long long ll;
    typedef tuple<ll, ll, ll, ll> tup;
    bool overlap(tup& rect1, tup& rect2) {
        auto [bl_x1, bl_y1, tr_x1, tr_y1] = rect1;
        auto [bl_x2, bl_y2, tr_x2, tr_y2] = rect2;

        if (bl_x1 >= tr_x2) return false;
        if (bl_x2 >= tr_x1) return false;
        if (bl_y1 >= tr_y2) return false;
        if (bl_y2 >= tr_y1) return false;
        return true;
    }
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        int n = bottomLeft.size();
        vector<tup> rectangles(n);
        for (int i = 0; i < n; i++) {
            rectangles[i] = {bottomLeft[i][0], bottomLeft[i][1], 
                topRight[i][0], topRight[i][1]};
        }

        ll area = 0;
        int i, j;
        for (i = 0; i < n; i++) {
            for (j = i + 1; j < n; j++) {
                if (overlap(rectangles[i], rectangles[j])) {
                    auto [bl_x1, bl_y1, tr_x1, tr_y1] = rectangles[i];
                    auto [bl_x2, bl_y2, tr_x2, tr_y2] = rectangles[j];

                    ll bl_x = max(bl_x1, bl_x2);
                    ll bl_y = max(bl_y1, bl_y2);
                    ll tr_x = min(tr_x1, tr_x2);
                    ll tr_y = min(tr_y1, tr_y2);

                    ll l = min(tr_x - bl_x, tr_y - bl_y);
                    area = max(area, l * l);
                }
            }
        }
        return area;
    }
};