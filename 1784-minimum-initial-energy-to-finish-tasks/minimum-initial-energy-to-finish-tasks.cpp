#define debug(x) cout << #x << " is " << x << endl;

class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] - a[0] > b[1] - b[0];
        });

        int energy = 0;
        int ret = 0;
        for (int i = 0; i < tasks.size(); i++) {
            int actual = tasks[i][0];
            int minimum = tasks[i][1];

            ret += max(minimum - energy, 0);
            energy = max(energy, minimum);
            energy -= actual;
        }
        return ret;
    }
};