struct Node {
    int min_val;
    int max_val;
    int lazy;
};

class SegmentTree {
    int n;
    vector<Node> tree;
public:
    SegmentTree(int size) : n(size) {
        tree.resize(4 * n, {0, 0, 0});
    }

    void push(int node, int s, int e) {
        if (tree[node].lazy) {
            if (s + 1 < e) {
                tree[2 * node].lazy += tree[node].lazy;
                tree[2 * node].min_val += tree[node].lazy;
                tree[2 * node].max_val += tree[node].lazy;

                tree[2 * node + 1].lazy += tree[node].lazy;
                tree[2 * node + 1].min_val += tree[node].lazy;
                tree[2 * node + 1].max_val += tree[node].lazy;
            }

            tree[node].lazy = 0;
        }
    }

    void pull(int node) {
        tree[node].min_val = min(tree[2 * node].min_val, tree[2 * node + 1].min_val);
        tree[node].max_val = max(tree[2 * node].max_val, tree[2 * node + 1].max_val);
    }

    void update(int node, int s, int e, int l, int r, int val) {
        if (r <= s || l >= e) return;

        if (l <= s && e <= r) {
            tree[node].min_val += val;
            tree[node].max_val += val;
            tree[node].lazy += val;
            return;
        }

        push(node, s, e);
        int m = (s + e)/2;
        update(2 * node, s, m, l, r, val);
        update(2 * node + 1, m, e, l, r, val);
        pull(node);
    }

    int query(int node, int s, int e, int l, int r) {
        if (r <= s || l >= e) return -1;
        if (tree[node].min_val > 0 || tree[node].max_val < 0) return -1; 
        

        if (s + 1 == e)
            return (tree[node].min_val == 0) ? s : -1;

        push(node, s, e);
        int m = (s + e)/2;
        int left_res = query(2 * node, s, m, l, r);
        if (left_res != -1) return left_res;

        return query(2 * node + 1, m, e, l, r);
    }

    void add_range(int l, int r, int val) {
        update(1, 0, n, l, r, val);
    }

    int query_leftmost_zero(int r_bound) {
        return query(1, 0, n, 0, r_bound);
    }
};
class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        SegmentTree st(n);
        map<int, int> last_pos;
        int max_len = 0;

        for (int r = 0; r < n; ++r) {
            int val = nums[r];
            int prev_r = last_pos.count(val) ? last_pos[val] : -1;

            int direction = (val % 2 == 0) ? 1 : -1;

            st.add_range(prev_r + 1, r + 1, direction);

            last_pos[val] = r;

            int l_min = st.query_leftmost_zero(r + 1);
            if (l_min != -1)
                max_len = max(max_len, r - l_min + 1);
        }
        return max_len;
    }
};