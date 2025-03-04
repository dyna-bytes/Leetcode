class Solution {
public:
    typedef long long ll;
    int mostBooked(int n, vector<vector<int>>& meetings) {
        set<int> available_rooms;
        for (int i = 0; i < n; i++) available_rooms.insert(i);

        priority_queue<pair<ll, ll>,
            vector<pair<ll, ll>>,
            greater<pair<ll, ll>> > handling_meetings; // {e, room}

        sort(meetings.begin(), meetings.end());

        ll max_meeting = 0;
        vector<ll> rooms(n, 0);
        for (int i = 0; i < meetings.size(); i++) {
            while (!handling_meetings.empty() && 
            handling_meetings.top().first <= meetings[i][0]) {
                auto [e, room] = handling_meetings.top();
                handling_meetings.pop();
                available_rooms.insert(room);
            }

            ll delayed = 0;
            if (available_rooms.empty() && !handling_meetings.empty()) {
                delayed = handling_meetings.top().first - meetings[i][0];
                auto [e, room] = handling_meetings.top();
                handling_meetings.pop();
                available_rooms.insert(room);
            }

            int room = *available_rooms.begin();
            available_rooms.erase(available_rooms.begin());

            handling_meetings.push({meetings[i][1] + delayed, room});

            max_meeting = max(++rooms[room], max_meeting);
        }

        for (int i = 0; i < n; i++)
            if (rooms[i] == max_meeting)
                return i;
        return -1;
    }
};