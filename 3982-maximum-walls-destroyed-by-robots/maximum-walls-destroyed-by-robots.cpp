class Solution {
    typedef struct {
        int idx;
        int pos;
        int dist;
    } robot_t;
    int n;
    vector<int> robots, dists, walls;
    vector<vector<int>> dp;
    const int L = 0, R = 1;
    const int INF = 2e9 + 7;

    int f(int i, int shoot_right) {
        if (i >= n) return 0;

        int left_robot = (i == 0) ? -INF : robots[i-1];
        int right_robot = robots[i+1];
        function<int(int, int)> get_range = [&](int l, int r) {
            if (l > r) return 0;
            return (int)(upper_bound(walls.begin(), walls.end(), r)
                - lower_bound(walls.begin(), walls.end(), l));
        };

        int& ret = dp[i][shoot_right];
        if (ret != -1) return ret;

        left_robot++;
        right_robot--;

        if (shoot_right) {
            ret = f(i + 1, true) + get_range(robots[i], min(right_robot, robots[i] + dists[i]));

            int ceiling = max(robots[i], robots[i + 1] - dists[i + 1]);
            int right_bound = min(ceiling - 1, robots[i] + dists[i]);

            ret = max(ret, f(i + 1, false) + get_range(robots[i], right_bound));
        } else {
            ret = max(f(i + 1, false), f(i + 1, true)) 
                + get_range(max(left_robot, robots[i] - dists[i]), robots[i]);
        }

        return ret;
    }
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        n = robots.size();
        vector<robot_t> bots(n);
        for (int i = 0; i < n; i++) 
            bots[i] = { i, robots[i], distance[i] };
        
        sort(bots.begin(), bots.end(), [](robot_t& a, robot_t& b) {
            return a.pos < b.pos;
        });

        this->robots.assign(n + 1, 0);
        this->dists.assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            this->robots[i] = bots[i].pos;
            this->dists[i] = bots[i].dist;
        }
        this->robots[n] = INF;
        this->dists[n] = INF; 

        sort(walls.begin(), walls.end());
        this->walls = walls;
        dp.assign(n + 1, vector<int>(2, -1));
        return max(f(0, false), f(0, true));
    }
};