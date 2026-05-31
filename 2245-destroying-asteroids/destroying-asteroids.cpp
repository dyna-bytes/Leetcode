class Solution {
    typedef long long ll;
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        sort(asteroids.begin(), asteroids.end());
        ll m = mass;
        for (ll a: asteroids) {
            if (m >= a) m += a;
            else return false;
        }
        return true;
    }
};