#define debugVect(v) do { \
    cout << #v << " is |"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)

class Solution {
public:
    vector<int> getModifiedArray(int n, vector<vector<int>>& updates) {
        vector<int> delta(n+1, 0);
        for (vector<int>& update: updates) {
            int s = update[0], e = update[1] + 1, inc = update[2];

            delta[s] += inc;
            delta[e] -= inc;
        }
        // debugVect(delta);

        vector<int> arr(n, 0);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += delta[i];
            arr[i] = sum;
        }
        return arr;
    }
};