class Solution {
    typedef pair<int, int> pii;
public:
    string reorganizeString(string s) {
        unordered_map<int, int> freq;
        for (char c: s) freq[c]++;

        priority_queue<pii> pq;
        for (auto [c, f]: freq) pq.push({f, c});

        string ret;
        char last_c = 0;
        while (pq.size()) {
            auto [f, c] = pq.top(); pq.pop();
            if (last_c == c) {
                if (pq.empty()) return "";
                
                auto [next_f, next_c] = pq.top(); pq.pop();
                pq.push({f, c});
                f = next_f, c = next_c;
            }

            ret.push_back(c);
            last_c = c;
            if (--f > 0) pq.push({f, c});
        }
        return ret;
    }
};