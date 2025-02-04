class Solution {
public:
    int candy(vector<int>& ratings) {
        int N = ratings.size();
        vector<int> upside(N, 0), downside(N, 0);

        for (int i = 0; i < N-1; i++) {
            if (ratings[i] < ratings[i+1]) upside[i+1]+=(upside[i]+1);
        }

        for (int i = N-1; i > 0; i--) {
            if (ratings[i] < ratings[i-1]) downside[i-1]+=(downside[i]+1);
        }

        int cnt = N;
        for (int i = 0; i < N; i++)
            cnt += max(upside[i], downside[i]);
        return cnt;
    }
};
