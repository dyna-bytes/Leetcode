class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> available_servers;
        priority_queue<pair<int, int>, vector<pair<int, int>>, 
            greater<pair<int, int>>> handling_works; // {ending time, index}
        vector<int> works(k, 0);

        for (int i = 0; i < k; i++) available_servers.insert(i);
        
        int max_work = 0;
        for (int i = 0; i < arrival.size(); i++) {
            while (!handling_works.empty() && 
            handling_works.top().first <= arrival[i]) {
                auto [_, server] = handling_works.top();
                handling_works.pop();
                available_servers.insert(server);
            }

            if (available_servers.empty()) continue;

            auto it = available_servers.lower_bound(i % k);
            if (it == available_servers.end()) it = available_servers.begin();
            int server = *it;
            available_servers.erase(it);

            handling_works.push({arrival[i]+load[i], server});
            max_work = max(++works[server], max_work);
        }

        vector<int> busiest;
        for (int i = 0; i < k; i++)
            if (max_work == works[i])
                busiest.push_back(i);

        return busiest;
    }
};