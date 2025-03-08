class Solution {
public:
    typedef long long ll;
    int racecar(int target) {
        map<pair<ll, ll>, bool> visited;
        queue<pair<ll, ll>> q;
        q.push({0, 1});
        visited[{0, 1}] = true;

        for (int step = 0; !q.empty(); step++) {
            for (int level = q.size(); level > 0; level--) {
                auto [pos, speed] = q.front();
                q.pop();

                if (pos == target)
                    return step;

                pair<ll, ll> forward = {pos + speed, speed * 2};
                if (!visited[forward] && 0 < pos + speed &&
                    pos + speed < target * 2) {
                    q.push(forward);
                    visited[forward] = true;
                }

                pair<ll, ll> backward = {pos, speed > 0 ? -1 : 1};
                if (!visited[backward] && 0 < pos && pos < target * 2) {
                    q.push(backward);
                    visited[backward] = true;
                }
            }
        }

        return -1;
    }
};