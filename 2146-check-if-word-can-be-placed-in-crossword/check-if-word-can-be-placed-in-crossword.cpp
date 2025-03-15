class Solution {
    const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
public:
    bool placeWordInCrossword(vector<vector<char>>& board, string word) {
        int Y = board.size();
        int X = board[0].size();
        string reversed = word;
        reverse(reversed.begin(), reversed.end());

        auto match = [&](string& str, string& word) {
            for (int i = 0; i < str.size(); i++) {
                if (str[i] == ' ') continue;
                if (str[i] == word[i]) continue;
                return false;
            }
            return true;
        };

        for (int y = 0, e; y < Y; y++) {
            for (int s = 0; s < X; s++) {
                if (board[y][s] == '#') continue;
                string str;
                str += board[y][s];
                for (e = s + 1; e < X; e++) {
                    if (board[y][e] == '#') break;
                    str += board[y][e];
                }
                s = e;

                // [s, e)
                if (str.size() != word.size()) continue;
                if (match(str, word) || match(str, reversed))
                    return true;
            }
        }

        for (int x = 0; x < X; x++) {
            cout << "x = " << x << endl;
            for (int s = 0, e; s < Y; s++) {
                if (board[s][x] == '#') continue;
                string str;
                str += board[s][x];
                for (e = s + 1; e < Y; e++) {
                    if (board[e][x] == '#') break;
                    str += board[e][x];
                }
                s = e;

                // [s, e)
                if (str.size() != word.size()) continue;
                if (match(str, word) || match(str, reversed))
                    return true;
            }
        }
        
        return false;
    }
};