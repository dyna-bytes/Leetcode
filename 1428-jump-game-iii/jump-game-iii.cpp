class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        vector<bool> visited(n, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        auto inRange = [&](int idx) {
            return 0 <= idx && idx < n;
        };

        while (q.size()) {
            int cur_idx = q.front(); q.pop();
            int cur_val = arr[cur_idx];
            if (cur_val == 0) return true;

            if (inRange(cur_idx  + cur_val) 
            && !visited[cur_idx + cur_val]) {
                visited[cur_idx + cur_val] = true;
                q.push(cur_idx + cur_val);
            }

            if (inRange(cur_idx - cur_val)
            && !visited[cur_idx - cur_val]) {
                visited[cur_idx - cur_val] = true;
                q.push(cur_idx - cur_val);
            }
        }

        return false;
    }
};