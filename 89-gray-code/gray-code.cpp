class Solution {
public:
    int N;
    int powerN;
    unordered_set<int> hash;

    bool search(int item, unordered_set<int>& hash) {
        auto elem = hash.find(item);
        if (elem == hash.end()) return false;
        return true;
    }

    bool check(int front, int back) {
        auto first = bitset<16>(front);
        auto second = bitset<16>(back);
        int unmatch = 0;
        for (int i = 0; i < N; i++) {
            if (first[i] != second[i])
                unmatch++;

            if (unmatch >= 2) return false;
        }

        return (unmatch == 1);
    }

    int dfs(int n, vector<int>& ret) {
        if (ret.size() == powerN) {
            if (check(ret.front(), ret.back()))
                return true;
            return false;
        }

        int last = ret.back();
        auto last_bit = bitset<16>(last);
        for (int i = 0; i < (n+1); i++) {
            auto try_bit = last_bit;

            // try bitflip
            try_bit[i] = !try_bit[i];
            int try_int = try_bit.to_ulong();
            if (search(try_int, hash))
                continue;

            ret.push_back(try_int);
            hash.insert(try_int);

            if (dfs(n+1, ret))
                return true;

            ret.pop_back();
            hash.erase(try_int);
        }

        return false;
    }

    vector<int> grayCode(int n) {
        vector<int> ret;
        N = n;
        powerN = pow(2, n);
        ret.reserve(powerN);

        ret.push_back(0);
        hash.insert(0);
        dfs(1, ret);

        return ret;
    }
};