class Solution {
    void leftshift(vector<int>& row) {
        int front = row.front();
        for (int i = 0; i < row.size() - 1; i++)
            row[i] = row[i + 1];
        row.back() = front;
    }

    void rightshift(vector<int>& row) {
        int back = row.back();
        for (int i = row.size() - 2; i >= 0; i--)
            row[i + 1] = row[i];
        row.front() = back;
    }
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        auto ori = mat;

        while (k--) {
            for (int i = 0; i < mat.size(); i++) {
                if (i % 2 == 0) leftshift(mat[i]);
                else rightshift(mat[i]);
            }
        }

        return ori == mat;
    }
};