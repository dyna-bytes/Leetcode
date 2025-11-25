class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        int R1 = mat1.size();
        int C1 = mat1[0].size();
        int R2 = mat2.size();
        int C2 = mat2[0].size();
        assert(C1 == R2);

        unordered_map<int, vector<int>> um;
        vector<vector<int>> res(R1, vector<int>(C2, 0));

        for (int r = 0; r < R2; r++)
            for (int c = 0; c < C2; c++)
                if (mat2[r][c]) um[r].push_back(c);

        for (int r = 0; r < R1; r++)
            for (int c = 0; c < C1; c++)
                for (int k: um[c])
                    res[r][k] += mat1[r][c] * mat2[c][k];
        return res;
    }
};