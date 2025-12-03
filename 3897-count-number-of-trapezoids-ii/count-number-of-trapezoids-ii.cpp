class Solution {
    typedef long long ll;
    typedef pair<int, int> pii;
public:
    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();

        map<pii, map<ll, map<ll, int>>> vectors;
        // { slope: { y-intercept: { len: count } } }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int dx = points[i][0] - points[j][0];
                int dy = points[i][1] - points[j][1];

                ll len = dx*dx + dy*dy;

                if (dx < 0 || (dx == 0 && dy < 0))
                    dx = -dx, dy = -dy;

                int g = __gcd(dx, dy);
                dx = dx/g, dy = dy/g;
                ll C = dx*points[i][1] - dy*points[i][0];
                vectors[{ dx, dy }][C][len]++;
            }
        }

        int trapezoids = 0;
        int parallelograms = 0;
        for (auto& [slope, lines]: vectors) {
            // transform map to vector for easier double looping.
            vector<map<ll, int>*> lineGroups;
            for (auto& [C, lenMap]: lines)
                lineGroups.push_back(&lenMap);

            for (int i = 0; i < lineGroups.size(); i++) {
                for (int j = i + 1; j < lineGroups.size(); j++) {
                    auto& groupA = *lineGroups[i]; // map<len, count>
                    auto& groupB = *lineGroups[j]; // map<len, count>

                    int countA = 0;
                    for (auto& [len, cnt]: groupA) countA += cnt;

                    int countB = 0;
                    for (auto& [len, cnt]: groupB) countB += cnt;

                    trapezoids += countA * countB;

                    for (auto& [len, cnt]: groupA) {
                        if (groupB.count(len))
                            parallelograms += cnt * groupB[len];
                    }
                }
            }
        }
        return trapezoids - parallelograms/2;
    }
};