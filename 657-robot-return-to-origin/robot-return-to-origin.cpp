class Solution {
    const int dy[4] = {0, 0, -1, 1}, dx[4] = {1, -1, 0, 0};
    char dir['Z'];
public:
    bool judgeCircle(string moves) {
        dir['R'] = 0;
        dir['L'] = 1;
        dir['U'] = 2;
        dir['D'] = 3;

        int y = 0, x = 0;
        for (char move: moves) {
            int d = dir[move];
            y += dy[d], x += dx[d];
        }

        return y == 0 && x == 0;
    }
};