class Solution {
    bool isVowel(const char& c) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') 
            return true;
        return false;
    }
public:
    string reverseVowels(string s) {
        vector<char> vowels;
        for (char& c: s)
            if (isVowel(c)) vowels.push_back(c);

        for (char& c: s) {
            if (isVowel(c)) {
                c = vowels.back();
                vowels.pop_back();
            }
        }
        return s;
    }
};