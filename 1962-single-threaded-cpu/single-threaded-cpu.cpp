// #define DBG
#ifdef DBG
#define debug(x) std::cout << "[ " << __func__ << "](" << __LINE__ << ") " << #x << " is " << x << endl
#else
#define debug(x)
#endif

class Solution {
    typedef long long ll;
    typedef vector<ll> vll; // {enqueue time, processing time, index}
    struct cmp{
        bool operator()(vll& a, vll& b) {
            if (a[1] == b[1]) return a[2] > b[2];
            return a[1] > b[1];
        }
    };

public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        vector<vll> enqueue;
        for (int i = 0; i < tasks.size(); i++) 
            enqueue.push_back({tasks[i][0], tasks[i][1], i});

        sort(enqueue.begin(), enqueue.end());

        vector<int> ret;
        priority_queue<vll, vector<vll>, cmp> availables;
    
        ll t = 0;
        for (int i = 0; i < enqueue.size(); ) {
            debug(t);
            if (availables.empty() && t < enqueue[i][0]) 
                t = enqueue[i][0];
            
            while (i < enqueue.size() && t >= enqueue[i][0]) {
                availables.push(enqueue[i]);
                debug(enqueue[i][2]);
                i++;
            }

            if (!availables.empty()) {
                const vll& proc = availables.top();
                debug(proc[2]);
                ret.push_back(proc[2]);
                t += proc[1];
                availables.pop();
            }
        }
        
        while (!availables.empty()) {
            const vll& proc = availables.top();
            debug(proc[2]);
            ret.push_back(proc[2]);
            t += proc[1];
            availables.pop();
        }
        return ret;
    }
};