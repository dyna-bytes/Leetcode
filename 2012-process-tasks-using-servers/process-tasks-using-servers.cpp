// #define DBG
#ifdef DBG
#define debug(x)                                                               \
    std::cout << "[ " << __func__ << "](" << __LINE__ << ") " << #x << " is "  \
              << x << endl
#else
#define debug(x) (0)
#endif
class Solution {
typedef tuple<int, int, int> tiii; // server {weight, index, end time}
struct cmp {
    bool operator() (tiii& a, tiii& b) {
        return get<2>(a) > get<2>(b);
    }
};
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        priority_queue<tiii, vector<tiii>, greater<tiii>> availables;
        priority_queue<tiii, vector<tiii>, cmp> holdings;
        vector<int> ans(tasks.size());

        for (int i = 0; i < servers.size(); i++)
            availables.push({servers[i], i, 0});

        int time = 0;
        for (int t = 0; t < tasks.size(); t++) {
            time = max(time, t);
            debug(time);
            while (!holdings.empty() && get<2>(holdings.top()) <= time) {
                availables.push(holdings.top());
                holdings.pop();
            }

            if (availables.empty()) {
                int last_time = get<2>(holdings.top());
                time = max(time, last_time);
                while (!holdings.empty() && get<2>(holdings.top()) <= time) {
                    availables.push(holdings.top());
                    holdings.pop();
                }
            }

            auto [weight, index, end_time] = availables.top();
            availables.pop();
            debug(index);

            time = max(time, end_time);
            holdings.push({weight, index, time + tasks[t]});
            ans[t] = index;
        } 
        return ans;
    }
};