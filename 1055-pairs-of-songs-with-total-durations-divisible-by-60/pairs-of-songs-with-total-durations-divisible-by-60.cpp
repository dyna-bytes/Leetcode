class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& times) {
        int n = times.size();
        unordered_map<int, int> um;

        int cnt = 0;
        for (int time: times) {
            time %= 60;
            if (um.count((60 - time) % 60))
                cnt += um[(60 - time) % 60];
            um[time]++;
        }
        return cnt;
    }
};

/*
[30, 20, 30, 40, 40]
*/