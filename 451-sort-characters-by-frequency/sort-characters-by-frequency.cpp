class Solution {
    typedef pair<int, int> pii;
public:
    string frequencySort(string s) {
        string ret;
        unordered_map<char, int> um;
        for (char& c: s) um[c]++;

        priority_queue<pii, vector<pii>, less<pii>> pq;
        for (auto& [c, f]: um) pq.push({f, c});

        while (pq.size()) {
            auto [f, c] = pq.top(); pq.pop();

            ret.append(string(f, c));
        }
        return ret;
    }
};