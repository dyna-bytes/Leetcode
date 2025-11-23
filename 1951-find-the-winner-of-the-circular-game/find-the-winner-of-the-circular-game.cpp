#define debug(x) cout << #x << " is " << x << endl;
class Solution {
public:
    int findTheWinner(int n, int k) {
        queue<int> q;
        for (int i = 1; i <= n; i++)
            q.push(i);

        queue<int> buf;

        while (n > 1) {
            int run = (k - 1) % n + 1;
            for (int i = 1; i < run; i++) {
                buf.push(q.front());
                q.pop();
            }
            debug(n);
            debug(q.front());
            q.pop();
            debug(buf.front());
            
            while (buf.size()) {
                q.push(buf.front());
                buf.pop();
            }
            n--;
        }
        return q.front();
    }
};