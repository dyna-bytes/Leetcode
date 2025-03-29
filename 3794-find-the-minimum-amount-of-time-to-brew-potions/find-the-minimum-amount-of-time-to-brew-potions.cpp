class Solution {
    typedef long long ll;
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        int N = skill.size();
        int M = mana.size();
        vector<ll> f(N, 0); // wizard's earliest free time for the last potion

        for (int x: mana) {
            ll now = f[0];
            for (int i = 1; i < N; i++)
                now = max(now + skill[i-1] * x, f[i]);
            f[N-1] = now + skill[N-1] * x;

            for (int i = N-2; i >= 0; i--)
                f[i] = f[i+1] - skill[i+1] * x; 
        }
        return f[N-1];
    }
};