struct SegTree {
    int size;
    vector<int> tree;
    SegTree(int n) {
        size = 1;
        while (size < n) size *= 2;
        size *= 2;
        tree.resize(size + 1);
    }
    void construct() {
        for (int i = size/2 - 1; i > 0; i--)
            tree[i] = max(tree[i*2], tree[i*2+1]);
    }

    /** -------- recursive version -------- **/
    void insert(int idx, int val) { insert(1, 0, size/2, idx, val); }
    void insert(int node, int s, int e, int idx, int val) {
        if (idx < s || e <= idx) return; // idx ∈ [s, e) 가 아니면 return
        if (s+1 == e) { // 리프 노드
            tree[node] = val;
            return;
        }
        int mid = (s + e) / 2;
        insert(node*2, s, mid, idx, val);
        insert(node*2+1, mid, e, idx, val);
        tree[node] = max(tree[node*2], tree[node*2+1]);
    }

    // max in range of [s, e)
    int query(int s, int e) { return query(1, 0, size/2, s, e); }
    int query(int node, int ns, int ne, int s, int e) {
        if (ne <= s || e <= ns) return INT_MIN; // 겹치지 않으면 최소값 반환
        if (s <= ns && ne <= e) return tree[node]; // 완전히 포함되면 값 반환

        int mid = (ns + ne) / 2;
        return max(query(node*2, ns, mid, s, e),
                   query(node*2+1, mid, ne, s, e));
    }
};

class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        int max_x = 0;
        for (auto& q: queries) max_x = max(max_x, q[1]);

        int limit = max_x + 2;
        SegTree st(limit);
        set<int> obstacles;
        obstacles.insert(0);
        obstacles.insert(limit);

        vector<bool> results;

        for (auto& q: queries) {
            if (q[0] == 1) {
                int x = q[1];
                auto it = obstacles.upper_bound(x);
                int nxt = *it;
                int prv = *prev(it);

                st.insert(x, x - prv); // [prv, x] 구간의 길이 저장
                st.insert(nxt, nxt - x); // [x, nxt] 구간의 길이 저장
                obstacles.insert(x);
            } else {
                int x = q[1];
                int sz = q[2];

                auto it = obstacles.upper_bound(x);
                int prv = *prev(it);
                int max_complete = st.query(0, prv + 1);
                int incomplete_len = x - prv;
                if (max(max_complete, incomplete_len) >= sz)
                    results.push_back(true);
                else
                    results.push_back(false);
            }
        }
        return results;
    }
};