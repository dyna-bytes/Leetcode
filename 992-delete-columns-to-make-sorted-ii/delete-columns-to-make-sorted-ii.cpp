class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int Y = strs.size();
        int X = strs[0].size();
        vector<bool> sorted(Y-1, false);

        int del = 0;
        for (int x = 0; x < X; ++x) {
            queue<int> q;
            for (int y = 0; y < Y-1; ++y) {
                if (sorted[y]) continue;

                if (strs[y][x] > strs[y + 1][x]){
                    del++;
                    while (q.size()) {
                        sorted[q.front()] = false;
                        q.pop();
                    }
                    break;
                } else if (strs[y][x] < strs[y + 1][x]) {
                    sorted[y] = true;
                    q.push(y);
                }
            }
        }

        return del;
    }
};

/*
 vdy
 vei
 zvc
 zid

 abx
 agz
 bgc
 bfc
*/