#define debug(x) cout << #x << " is " << x << endl;

class Solution {
    double below_area(vector<int>& square, double horizon) {
        int y0 = square[1];
        double l = square[2];
        int y1 = y0 + l;

        if (y0 >= horizon) return 0;
        if (y1 <= horizon) return l * l;

        return (horizon - y0) * l;
    }
    double diff(vector<vector<int>>& squares, double horizon) {
        double below_sum = 0.0;
        double total_sum = 0.0;
        
        for (auto& sq : squares) {
            double l = sq[2];
            total_sum += l * l;
            below_sum += below_area(sq, horizon);
        }
        
        return 2 * below_sum - total_sum;
    }
public:
    double separateSquares(vector<vector<int>>& squares) {
        double min_y = 2e9;
        double max_y = 0;
        
        // Determine the search range based on all squares
        for (const auto& sq : squares) {
            min_y = min(min_y, (double)sq[1]);
            max_y = max(max_y, (double)sq[1] + sq[2]);
        }

        double lo = min_y;
        double hi = max_y;

        for (int i = 0; i < 100; ++i) {
            double m = (hi + lo) / 2;
            if (diff(squares, m) >= 0) {
                hi = m;
            } else {
                lo = m;
            }
        }
        
        return lo;
    }
};