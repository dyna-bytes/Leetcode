class Solution {
public:
    bool twoPointers(string& start, string& result) {
        int s = 0, r = 0;

        while (s < start.size() || r < result.size()) {
            char s_char = start[s];
            char r_char = result[r];
            if (s_char == 'X') {
                s++;
                continue;
            }

            if (r_char == 'X') {
                r++;
                continue;
            }

            if (s_char == 'L' && r_char == 'L') {
                if (s < r) return false;
                s++, r++;
            } else if (s_char == 'R' && r_char == 'R') {
                if (s > r) return false;
                s++, r++;
            } else
                return false;
        }
        return true;
    }

    bool canTransform(string start, string result) {
        auto check_frequency = [](string& start, string& result) {
            tuple<int, int, int> srt(0, 0, 0), res(0, 0, 0);
            for (char& c: start) {
                auto& [L, X, R] = srt;
                if (c == 'L') L++;
                else if (c == 'X') X++;
                else if (c == 'R') R++;
            }
            for (char& c: result) {
                auto& [L, X, R] = res;
                if (c == 'L') L++;
                else if (c == 'X') X++;
                else if (c == 'R') R++;
            }

            return (srt == res);
        };

        if (!check_frequency(start, result))
            return false;

        return twoPointers(start, result);
    }
};

/*
XL -> LX
RX -> XR

----
LR <-> RL  (x) // L and R can not cross each other
XRX ->RXX  (x),  RXX ->XRX  (o) // R can not go left to X
XLX -> XXL  (x),  XXL -> XLX  (o) // L can not go right to X

----
1. The frequency of 'X', 'R', and 'L' should be the same in both the start and result strings.
2. Use two pointers: one for the start string and one for the result string
3. Move the pointers until you encounter 'R' or 'L' in both strings.
4. If the characters you find are not the same, it's impossible to transform the `start` string into the `result`. Return `false`.
5. If the characters are the same (either 'L' and 'L' or 'R' and 'R'):
		a) For 'L' and 'L' : Ensure that the index of 'L' in `start` is not less than its index in `result`, as 'L' cannot move to the right.
		b) For 'R' and 'R' : Ensure that the index of 'R' in `start` is not greater than its index in `result`, as 'R' cannot move to the left.
6. Perfom step 4 & 5 until your pointer reaches to the end.
*/