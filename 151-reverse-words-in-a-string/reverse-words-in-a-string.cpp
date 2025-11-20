#define debug(x) cout << #x << " is " << x << endl;
class Solution {
public:
    string reverseWords(string s) {
        list<string> ls;

        int n = s.size();
        for (int i = 0, j = 0; i < n; ) {
            while (i < n && s[i] == ' ') i++;

            j = i;
            while (j < n && s[j] != ' ') j++;

            if (j > i)
                ls.insert(ls.end(), s.substr(i, j - i));
            i = j;
        }    

        ls.reverse();
        string ans;
        for (string& str: ls) 
            ans.append(str + " ");
        
        return ans.substr(0, ans.size() - 1);
    }
};