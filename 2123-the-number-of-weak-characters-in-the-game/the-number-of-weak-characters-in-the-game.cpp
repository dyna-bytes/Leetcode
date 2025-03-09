class Solution {
public:
    static bool cmp(vector<int>& p1, vector<int>& p2) {
        if (p1[0] == p2[0])
            return p1[1] > p2[1]; // for same attack, check the lower defense
                                  // values first
        return p1[0] < p2[0];
    }
    int numberOfWeakCharacters(vector<vector<int>>& properties) {
        sort(properties.begin(), properties.end(), cmp);

        int max_defense = 0;
        int ans = 0;

        for (int i = properties.size() - 1; i >= 0; i--) {
            // any props that have smaller defense value than max_defense
            // are weaker props
            if (properties[i][1] < max_defense)
                ans++;
            max_defense = max(max_defense, properties[i][1]);
        }
        return ans;
    }
};