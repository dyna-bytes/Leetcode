#define debug(x) cout << #x << " is " << x << endl;

class Solution {
public:
    int wordsTyping(vector<string>& sentence, int Y, int X) {
        ulong max_len = 0;
        for (string& str: sentence)
            max_len = max(max_len, str.size());

        if (max_len > X) return 0;

        int ret = 0;
        int x = 0;
        int k = 0;
        while (k < Y * X) {
            for (string& str: sentence) {
                if (x + str.size() == X) {
                    x = X;
                } else if (x + str.size() < X) {
                    x += str.size();
                } else {
                    k += (X - x);
                    x = str.size();
                }

                k += str.size();

                if (x == X) {
                    x = 0;
                } else {
                    x++;
                    k++;
                }
            }
            // debug(k);
            if (k <= Y * X)
                ret++;
        }
        return ret;
    }
};