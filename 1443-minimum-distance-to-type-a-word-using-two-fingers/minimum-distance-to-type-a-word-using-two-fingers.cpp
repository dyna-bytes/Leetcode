#define debug(x) cout << #x << " is " << x << endl;
class Solution {
    typedef pair<int, int> pii;
    int Y, X;
    vector<vector<char>> keyboard = {
        {'A', 'B', 'C', 'D', 'E', 'F'},
        {'G', 'H', 'I', 'J', 'K', 'L'},
        {'M', 'N', 'O', 'P', 'Q', 'R'},
        {'S', 'T', 'U', 'V', 'W', 'X'},
        {'Y', 'Z', '0', '0', '0', '0'},
    };
    map<char, pii> table;
    string word;
    int n;
    struct node {
        int idx;
        pii lhand, rhand;

        bool operator<(const node& other) const {
            if (idx != other.idx) return idx < other.idx;
            if (lhand != other.lhand) return lhand < other.lhand;
            return rhand < other.rhand;
        }
    };
    map<node, int> dp;

    int dist(const pii& a, const pii& b) {
        if (a == pii{-1, -1} || b == pii{-1, -1}) return 0;
        return abs(a.first - b.first) + abs(a.second - b.second);
    }

    int f(int idx, const pii& lhand, const pii& rhand) {
        if (idx >= n) return 0;

        int ch = word[idx];
        auto [ny, nx] = table[ch];

        if (dp.count({ idx, lhand, rhand })) return dp[{ idx, lhand, rhand }];

        int ret;
        ret = dist(lhand, {ny, nx}) + 
            f(idx + 1, {ny, nx}, rhand);
        
        ret = min(ret,
            dist(rhand, {ny, nx}) + f(idx + 1, lhand, {ny, nx}));
        return dp[{ idx, lhand, rhand }] = ret;
    }
public:
    int minimumDistance(string word) {
        this->word = word;
        n = word.size();
        Y = keyboard.size(), X = keyboard[0].size();
        for (int y = 0; y < Y; y++)
            for (int x = 0; x < X; x++)
                table[keyboard[y][x]] = { y, x };

        return f(0, {-1, -1}, {-1, -1});
    }
};