class Solution {
public:
    int dp[1001][1001];
    int f(int curr, int currWidth, int currHeight, vector<vector<int>>& books, int shelfWidth) {
        if (curr == books.size()) return 0;
        
        int& ret = dp[curr][currWidth];
        /*
        currHeight is implicitly handled by `curr` and `currWidth`,
        because the height is recalculated based on the maximum height 
        of books in the current configuration.
        */
        if (ret) return ret;

        ret = INT_MAX;

        int w = books[curr][0];
        int h = books[curr][1];
        // try to insert on current floor
        if (currWidth + w <= shelfWidth) {
            ret = min(ret, 
                max(h - currHeight, 0) + 
                f(curr+1, currWidth + w, max(currHeight, h), books, shelfWidth));
        }

        // try to build a new floor
        ret = min(ret, 
            h + f(curr+1, w, h, books, shelfWidth));
        return ret;
    }

    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        memset(dp, 0, sizeof(dp));
        int ret = f(0, 0, 0, books, shelfWidth);
        return ret;
    }
};