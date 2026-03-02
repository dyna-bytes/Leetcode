class Excel {
    typedef pair<int, int> pii;
    int height;
    char width;
    vector<vector<int>> mat;
    map<pii, vector<pii>> sums;

    int ctoi(char c) { return c - 'A'; }
    pii formatting(const string& f) {
        char col = f[0];
        int row = stoi(f.substr(1));
        return {row, ctoi(col)};
    }
    void propagate(pii& start) {
        queue<pii> q;
        q.push(start);
        
        while (q.size()) {
            pii curr = q.front(); q.pop();

            for (auto& [dep, sources]: sums) {
                bool isDependent = false;
                for (auto& src: sources) {
                    if (src == curr) {
                        isDependent = true;
                        break;
                    }
                }

                if (isDependent) {
                    int newVal = 0;
                    for (auto& src: sources)
                        newVal += mat[src.first][src.second];

                    if (mat[dep.first][dep.second] == newVal) continue;
                    mat[dep.first][dep.second] = newVal;
                    q.push(dep);
                }
            }
        }
    }
public:
    Excel(int height, char width) {
        this->height = height;
        this->width = width;
        mat.resize(height + 1, vector<int>(ctoi(width) + 1, 0));
    }
    
    void set(int row, char column, int val) {
        pii target = { row, ctoi(column) };
        sums[target].clear();
        mat[target.first][target.second] = val;

        propagate(target);
    }
    
    int get(int row, char column) {
        return mat[row][ctoi(column)];
    }
    
    int sum(int row, char column, vector<string> numbers) {
        pii target = { row, ctoi(column) };

        sums[target].clear();
        mat[target.first][target.second] = 0;

        for (string& num: numbers) {
            size_t pin;
            if ((pin = num.find(":")) == string::npos) {
                sums[target].push_back(formatting(num));
            } else {
                pii start = formatting(num.substr(0, pin));
                pii end = formatting(num.substr(pin + 1));

                for (int y = start.first; y <= end.first; ++y) {
                    for (int x = start.second; x <= end.second; ++x) {
                        sums[target].push_back({ y, x });
                    }
                }
            }
        }

        for (auto& [y, x]: sums[target])
            mat[target.first][target.second] += mat[y][x];

        propagate(target);
        return mat[target.first][target.second];
    }
};

/**
 * Your Excel object will be instantiated and called as such:
 * Excel* obj = new Excel(height, width);
 * obj->set(row,column,val);
 * int param_2 = obj->get(row,column);
 * int param_3 = obj->sum(row,column,numbers);
 */