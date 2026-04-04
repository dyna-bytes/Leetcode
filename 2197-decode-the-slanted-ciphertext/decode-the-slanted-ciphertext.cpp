class Solution {
public:
    string decodeCiphertext(string encodedText, int Y) {
        int n = encodedText.size();
        int X = n / Y;
        vector<vector<char>> mat(Y, vector<char>(X));
        int i = 0;
        int cnt = 0;
        for (int y = 0; y < Y; y++)
            for (int x = 0; x < X; x++) {
                mat[y][x] = encodedText[i++]; 
                if (mat[y][x] != ' ') cnt++;
            }

        string ret;
        int cnt2 = 0;
        for (int s = 0; s < X; s++) {
            for (int k = 0; k < Y; k++) {
                ret.push_back(mat[k][s + k]);
                if (mat[k][s + k] != ' ') cnt2++;
                if (cnt2 == cnt) return ret;
            }
        }
        return ret;
    }
};