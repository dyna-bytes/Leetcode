class Solution {
public:
    int compress(vector<char>& chars) {
        vector<char> s;
        for (int i = 0; i < chars.size(); ) {
            char curr = chars[i];
            int j;
            for (j = i; j < chars.size() && chars[j] == curr; j++);

            int cnt = j - i;
            s.push_back(curr);
            if (cnt > 1) {
                string num = to_string(cnt);
                for (char n: num) s.push_back(n);
            }
            i = j;
        }

        chars = s;
        return s.size();
    }
};