#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is |" <<; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)
class Solution {
    int n;
    vector<int> nums;
    vector<int> visited;
    int dfs(int i, bool type2, bool& containZero) {
        if (visited[i]) return 0;
        visited[i] = true;

        int num = nums[i];
        if (type2) {
            if (num == 0 && i == n-1) {
                containZero = true;
                return 1;
            } else if (num == i + 1) 
                return 1;

            if (num == 0) {
                containZero = true;
                return 1 + dfs(n - 1, type2, containZero);
            }
            return 1 + dfs(num - 1, type2, containZero);
        } else {
            if (num == 0) containZero = true;
            if (num == i) return 1;
            return 1 + dfs(num, type2, containZero);
        }
    }

    int case1() {
        visited.assign(n, 0);
        int L;
        int ret = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;
            bool containZero = false;
            L = dfs(i, false, containZero);
            if (containZero) ret += (L - 1);
            else if (L == 1) continue;
            else ret += (L + 1);
        }
        return ret;
    }
    int case2() {
        visited.assign(n, 0);
        int L;
        int ret = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;
            bool containZero = false;
            L = dfs(i, true, containZero);
            if (containZero) ret += (L - 1);
            else if (L == 1) continue;
            else ret += (L + 1);
        }
        return ret;
    }
public:
    int sortArray(vector<int>& nums) {
        this->nums = nums;
        this->n = nums.size();

        return min(case1(), case2());
    }
};