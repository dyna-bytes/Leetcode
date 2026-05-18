class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        queue<int> q;

        q.push(0);

        int farthest = minJump - 1;
        while (q.size()) {
            int i = q.front();
            q.pop();
            if (i == n - 1)
                return true;

            for (int j = max(i + minJump, farthest + 1);
                 j <= min(i + maxJump, n - 1); j++) {
                if (s[j] == '1')
                    continue;
                q.push(j);
            }
            farthest = max(farthest, min(i + maxJump, n - 1));
        }
        return false;
    }
};