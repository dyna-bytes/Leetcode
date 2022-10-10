class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> last;
        int len = 0, start = -1;
        for (int i = 0; i < s.size(); i++) {
            if (last.count(s[i]) && last[s[i]] > start) 
                start = last[s[i]]; // 현재 문자가 마지막으로 등장했던 위치를 가져옴
            
            last[s[i]] = i; // 현재 문자가 등장한 위치를 저장
            len = max(len, i - start);
        }
        return len;
    }
};