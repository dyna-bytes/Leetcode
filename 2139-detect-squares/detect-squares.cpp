class DetectSquares {
    unordered_map<int, vector<int>> ofX;
    void debug() {
        for (auto& [y, vint] : ofX) {
            cout << "[y] " << y << endl;
            for (auto x : vint)
                cout << x << " " << endl;
            cout << "----" << endl;
        }
    }
public:
    DetectSquares() {}

    void add(vector<int> point) {
        int x = point[0], y = point[1];

        ofX[y].push_back(x);
    }

    int count(vector<int> point) {
        int x = point[0], y = point[1];
        // cout << "{" << x << ", " << y << "}" << endl;
        // debug();

        auto scan_x_at_offset_y = [&](int x0, int x, int y) {
            int find_x0_at_y = 0, find_x_at_y = 0;

            for (int x1 : ofX[y]) {
                find_x_at_y += (x1 == x);
                find_x0_at_y += (x1 == x0);
            }
            
            return find_x_at_y * find_x0_at_y;
        };

        int cnt = 0;
        // search left or right point
        for (int x0 : ofX[y]) {
            if (x0 == x) continue;

            int len = abs(x0 - x);
            cnt += scan_x_at_offset_y(x0, x, y + len);
            cnt += scan_x_at_offset_y(x0, x, y - len);
        }

        return cnt;
    }
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */