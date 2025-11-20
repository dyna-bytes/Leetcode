#define debug(x) cout << #x << " is " << x << endl;
class Solution {
    typedef long long ll;
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        ll gtime = 0;
        unordered_map<ll, ll> um;
        for (int task: tasks) {
            gtime = max(gtime + 1, um.count(task) ? um[task] + space + 1 : 0);
            um[task] = gtime;
        }
        return gtime;
    }
};