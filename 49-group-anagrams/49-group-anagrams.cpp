class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<string> copy = strs;
        for(string& str: copy){
            sort(str.begin(), str.end());
        }

        vector<vector<string>> ans;
        unordered_map<string, int> hashmap;
        
        for(int index = 0; string sorted: copy){
            // debug(sorted);
            if(hashmap.find(sorted) != hashmap.end()){
                int push_to = hashmap[sorted];
                ans[push_to].push_back(strs[index]);
                // debug(push_to);
            }else{
                ans.push_back({strs[index]});
                hashmap.insert({sorted, ans.size() - 1});
                // debug(hashmap.count(sorted));
            }
            index++;
        }
        return ans;
    }
};