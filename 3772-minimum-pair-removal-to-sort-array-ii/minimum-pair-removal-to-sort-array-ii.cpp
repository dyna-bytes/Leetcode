#define debug(x) cout << #x << " is " << x << endl; 
#define debugVect(v) do { \
    cout << #v << " is |\t"; \
    for (auto e: v) cout << e << "\t|\t"; \
    cout << endl; \
} while (0)

class Solution {
    typedef long long ll;
    typedef pair<ll, ll> pll;
    map<ll, ll> arr;
    set<pll> sums;
    ll decreases = 0;
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++)
            arr[i] = nums[i];

        for (int i = 0; i < n - 1; i++) {
            sums.insert({ (ll)nums[i] + nums[i + 1], i });
            if (nums[i] > nums[i + 1]) decreases++;
        }

        int cnt = 0;
        while (decreases > 0) {
            auto [sum, idx] = *sums.begin();
            sums.erase(sums.begin());

            auto it = arr.find(idx);
            if (it == arr.end()) continue;

            auto next_it = next(it);
            if (next_it == arr.end()) continue;

            auto [_, curr_val] = *it;
            auto [_, next_val] = *next_it;
            if (curr_val + next_val != sum) continue;

            if (curr_val > next_val) decreases--;

            if (it != arr.begin()) {
                auto prev_it = prev(it);
                auto [_, prev_val] = *prev_it;
                if (prev_val > curr_val) decreases--;
            }

            auto next_next_it = next(next_it);
            if (next_next_it != arr.end()) {
                auto [_, next_next_val] = *next_next_it;
                if (next_val > next_next_val) decreases--;
            }

            arr[idx] = curr_val = sum;
            arr.erase(next_it);

            if (it != arr.begin()) {
                auto prev_it = prev(it);
                auto [prev_idx, prev_val] = *prev_it;
                if (prev_val > curr_val) decreases++;
                sums.insert({ prev_val + curr_val, prev_idx });
            }

            if (next_next_it != arr.end()) {
                auto [_, next_next_val] = *next_next_it;
                if (curr_val > next_next_val) decreases++;
                sums.insert({ curr_val + next_next_val, idx });
            }
            cnt++;
        }
        return cnt;
    }
};