class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        sort(strs.begin(), strs.end(), [](const string& a, const string& b){
            return a.size() > b.size();
        });

        unordered_set<string> duplications;
        unordered_set<string> candidates;
        for (string& str : strs) {
            if (candidates.find(str) != candidates.end())
                duplications.insert(str);
            else
                candidates.insert(str);
        }
        auto isIncluded = [&](string& str) {
            for (auto& dupl : duplications) {
                int i = 0, found = 0;
                for (int j = 0; i < str.size() && j < dupl.size(); i++, j++) {
                    while (j < dupl.size() && dupl[j] != str[i]) j++;
                    if (j < dupl.size() && dupl[j] == str[i]) found++;
                }
                if (found == str.size()) return true;
            }

            return false;
        };

        for (string& str : strs) {
            if (duplications.find(str) != duplications.end() || isIncluded(str))
                continue;
            return str.size();
        }
        return -1;
    }
};