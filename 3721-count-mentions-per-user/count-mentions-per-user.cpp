#define DBG
#ifdef DBG
#define debug(x) cout << #x << " is " << x << endl;
#else
#define debug(x)
#endif
class Solution {
public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        int n = numberOfUsers;
        sort(events.begin(), events.end(), [](vector<string>& l, vector<string>& r){
            int t1 = stoi(l[1]);
            int t2 = stoi(r[1]);
            
            if (t1 != t2)   
                return t1 < t2;            
            return l[0] == "OFFLINE";
        });

        unordered_map<int, int> off_time;
        unordered_map<int, int> offline;
        unordered_map<int, int> online;

        for (int i = 0; i < n; i++) online[i] = 0;

        int time = 0;
        for (vector<string>& event: events) {
            string cmd = event[0];
            int timestamp = stoi(event[1]);
            string users = event[2];
            debug(cmd);
            debug(timestamp);
            debug(users);

            for (auto it = off_time.begin(); it != off_time.end(); ) {
                auto [usr, time] = *it;
                if (time + 60 <= timestamp) {
                    it = off_time.erase(it);

                    online[usr] = offline[usr];
                    debug(usr);
                    debug(online[usr]);
                    offline.erase(usr);
                } else
                    it++;
            }

            if (cmd == "MESSAGE") {
                if (users == "ALL") {
                    for (auto& [usr, cnt]: offline)
                        cnt++;
                    for (auto& [usr, cnt]: online)
                        cnt++;
                } else if (users == "HERE") {
                    for (auto& [usr, cnt]: online) {
                        cnt++;          
                    }
                } else {
                    for (int i = 0, j = 0; i < users.size(); i++) {
                        if (users[i] == 'i') {
                            for (j = i + 1; j < users.size() && users[j] != ' '; j++) ;;
                            
                            i += 2;
                            int usr = stoi(users.substr(i, j - i));
                            debug(usr);
                            if (offline.count(usr)) offline[usr]++;
                            else if (online.count(usr)) online[usr]++;
                            i = j;
                        }
                    }
                }
            } else {
                int usr = stoi(users);
                offline[usr] = online[usr];
                online.erase(usr);
                off_time[usr] = timestamp;
            }
        }

        vector<int> ret(n, 0);
        for (auto& [usr, cnt]: offline)
            ret[usr] = cnt;
        for (auto& [usr, cnt]: online)
            ret[usr] = cnt;
        return ret;
    }
};