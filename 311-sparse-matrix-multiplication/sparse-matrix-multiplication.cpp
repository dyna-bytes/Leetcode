class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        unordered_map<int, unordered_map<int, int>> um1;
        unordered_map<int, unordered_map<int, int>> um2;

        int R1 = mat1.size();
        int C1 = mat1[0].size();
        int R2 = mat2.size();
        int C2 = mat2[0].size();
        assert(C1 == R2);

        for (int r = 0; r < R1; r++) 
            for (int c = 0; c < C1; c++)
                if (mat1[r][c])
                    um1[r][c] = mat1[r][c];

        for (int r = 0; r < R2; r++)
            for (int c = 0; c < C2; c++)
                if (mat2[r][c])
                    um2[r][c] = mat2[r][c];

        vector<vector<int>> res(R1, vector<int>(C2, 0));
        for (int r = 0; r < R1; r++) 
            for (int c = 0; c < C2; c++) 
                for (int i = 0; i < C1; i++) 
                    res[r][c] += um1[r][i] * um2[i][c];
          

        return res;
    }
};