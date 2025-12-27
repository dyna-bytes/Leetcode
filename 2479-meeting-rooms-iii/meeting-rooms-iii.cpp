class Solution {
    typedef long long ll;
    typedef pair<ll, ll> pll;
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        sort(meetings.begin(), meetings.end());

        priority_queue<ll, vector<ll>, greater<ll>> avails;
        priority_queue<pll, vector<pll>, greater<pll>> runnings; // {end, room}
        vector<ll> count(n, 0);

        for (int i = 0; i < n; i++)
            avails.push(i);

        for (vector<int>& meeting: meetings) {
            ll curr_s = meeting[0];
            ll curr_e = meeting[1];

            while (runnings.size() && 
                runnings.top().first <= curr_s) {
                auto [_, room] = runnings.top();
                runnings.pop();
                avails.push(room);
            }

            if (avails.size()) {
                int room = avails.top();
                avails.pop();

                count[room]++;
                runnings.push({curr_e, room});
            } else if (runnings.size()) {
                auto [prev_e, room] = runnings.top();
                runnings.pop();

                ll delay = prev_e - curr_s;
                if (delay > 0) 
                    curr_e += delay;
                
                count[room]++;
                runnings.push({curr_e, room});
            }
        }

        int max_count = 0;
        int rm = 0;
        for (int i = 0; i < n; i++) {
            if (max_count < count[i]) {
                max_count = count[i];
                rm = i;
            }
        }
        return rm;
    }
};