#define debug(x) cout << #x << " is " << x << endl;
class Solution {
    const int INF = 1e9;
    typedef pair<double, double> pdd;
    map<pdd, int> line; // { slope, y-intercept } : count
    set<pair<pdd, double>> visited;
    double get_slope(const pdd& point1, const pdd& point2) {
        auto [x1, y1] = point1;
        auto [x2, y2] = point2;

        if (x2 == x1) return INF;
        return (y2 - y1) / (x2 - x1);
    }
    
    double get_yintercept(const pdd& point, const double& slope) {
        auto [x, y] = point;
        if (slope == INF) return x;
        return y - slope*x;
    }
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        int maxpoints = 0;

        for (int i = 0; i < n; i++) {
            auto& point1 = points[i];
            int x1 = point1[0], y1 = point1[1];

            for (int j = i + 1; j < n; j++) {
                auto& point2 = points[j];
                int x2 = point2[0], y2 = point2[1];

                double a = get_slope({x1, y1}, {x2, y2});
                double b = get_yintercept({x1, y1}, a);
                if (visited.count({ { x2, y2 }, a })) continue;
                visited.insert( { {x2, y2}, a });
                maxpoints = max(maxpoints, ++line[{a, b}]);
            }
        }
        
        return maxpoints + 1;
    }
};