#define debug(x) cout << #x << " is " << x << endl;
class Solution {
public:
    int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
        int n = tiles.size();
        sort(tiles.begin(), tiles.end());
        vector<int> psum(n+1, 0);
        for (int i = 0; i < n; i++)
            psum[i+1]  = psum[i] + (tiles[i][1] - tiles[i][0] + 1);

        int maxCover = 0;
        for (int i = 0, j = 0; i < n; i++) {
            int l_i = tiles[i][0];
            int r_i = tiles[i][1];
            int carpetEnd = l_i + carpetLen;
            
            for (; j < n && tiles[j][0] < carpetEnd; j++)
                ;;
            j--;
            int l_j = tiles[j][0];
            int r_j = tiles[j][1];
            int cover = (psum[j] - psum[i]) + ((carpetEnd > r_j) ? psum[j+1] - psum[j] : carpetEnd - l_j);
            j++;
            // debug(i); debug(l_i); debug(r_i);
            // debug(j); debug(l_j); debug(r_j);
            // debug(psum[j]); debug(psum[i]);
            // debug(carpetEnd); debug(cover);
            maxCover = max(maxCover, cover);
        }
        return maxCover;
    }
};