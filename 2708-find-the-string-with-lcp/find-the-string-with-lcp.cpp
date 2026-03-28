#define debug(x) cout << #x << " is " << x << endl;
class UnionFind {
    vector<int> parent;
public:
    UnionFind(int n) {
        parent.resize(n, -1);
    }

    int find(int curr) {
        if (parent[curr] < 0) return curr;
        return parent[curr] = find(parent[curr]);
    }

    bool merge(int from, int to) {
        from = find(from);
        to = find(to);    
        if (from == to) return false;

        if (abs(parent[from]) > abs(parent[to])) swap(from, to);
        parent[to] += parent[from]; 
        parent[from] = to; 
        return true;
    }
    
    int count(int root) {
        root = find(root);
        return abs(parent[root]);
    }
};

class Solution {
    string greedyConstruct(vector<vector<int>>& lcp) {
        int n = lcp.size();
        UnionFind uf(n + 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (lcp[i][j] != lcp[j][i]) return "";
                if (lcp[i][j] > n - max(i, j)) return "";
                if (i == j && lcp[i][j] != n - i) return "";
                
                if (lcp[i][j] > 0) 
                    uf.merge(i, j);
            }
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (lcp[i][j] == 0 && uf.find(i) == uf.find(j))
                    return "";
        
        // greedy construction
        char arr[1001]; arr[n] = '\0';
        map<int, char> groupId;
        for (int i = 0; i < n; i++) {
            int root = uf.find(i);
            if (groupId.count(root) == 0) {
                if (groupId.size() >= 26) return "";
                groupId[root] = groupId.size() + 'a';
            }
            arr[i] = groupId[root];
        }
        return arr;
    }

    vector<vector<int>> constructLCP(const string& candi) {
        int n = candi.size();
        vector<vector<int>> lcp(n, vector<int>(n, 0));

        auto getLcpLen = [&](int i, int j) {
            int sz = 0;
            while (max(i, j) < n && candi[i] == candi[j]) {
                i++, j++;
                sz++;
            }
            return sz;
        };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                lcp[i][j] = lcp[j][i] = getLcpLen(i, j);
            }
        }
        return lcp;
    }
public:
    string findTheString(vector<vector<int>>& lcp) {
        string candi = greedyConstruct(lcp);
        if (candi.empty()) return "";
        
        if (lcp != constructLCP(candi)) return "";
        return candi;
    }
};