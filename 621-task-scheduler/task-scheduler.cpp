#define debug(x) cout << #x << " is " << x << endl;
class Solution {
    typedef pair<int, int> pii; 
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<int, int> freq;
        for (char task: tasks) freq[task]++;

        priority_queue<int> pq;
        for (auto [task, occ]: freq) 
            pq.push(occ);
        
        
        int time = 0;
        while (pq.size()) {
            int cycle = n + 1;
            int task_count = 0;
            vector<int> cache;
            while (cycle-- && pq.size()) {
                if (pq.top() > 1) cache.push_back(pq.top() - 1);
                pq.pop();
                task_count++;
            }

            for (int occ: cache)
                pq.push(occ);

            time += (pq.empty() ? task_count : n + 1);
        }
        return time;
    }
};