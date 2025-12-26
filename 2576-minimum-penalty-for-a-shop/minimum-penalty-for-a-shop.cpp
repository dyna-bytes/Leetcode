#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is " << "|"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)

class Solution {
public:
    int bestClosingTime(string customers) {
        int n = customers.size();
        vector<int> pref_y = vector<int>(n + 1, 0); 
        // pref_y[x] : [0, x], pref_y[b] - pref_y[a] = [a + 1, b] (whare b > a)
        vector<int> pref_n = vector<int>(n + 1, 0);
        // pref_n[x] : [x, n-1], pref_n[a] - pref_n[b] = [a, b - 1] (where b > a)
        
        for (int i = 0; i < n; i++) 
            pref_y[i] = (i > 0 ? pref_y[i - 1] : 0) + (customers[i] == 'Y');
        pref_y[n] = pref_y[n - 1];

        for (int i = n - 1; i >= 0; i--)
            pref_n[i] = pref_n[i + 1] + (customers[i] == 'N');

        int min_penalty = INT_MAX;
        int min_i;
        for (int i = 0; i <= n; i++) {
            int y_penalty = pref_y[n] - (i > 0 ? pref_y[i - 1] : 0);
            int n_penalty = pref_y[0] - pref_n[i];
            if (min_penalty > y_penalty + n_penalty) {
                min_penalty = y_penalty + n_penalty;
                min_i = i;
            }
        }
        return min_i;
    }
};