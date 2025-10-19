// #define DBG
#ifdef DBG
#define debug(x) cout << "[" << __func__ << "] " << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << "[" << __func__ << "]" << #v << " is |"; \
    for (auto e : v) cout << e << "|"; \
    cout << endl; \
}   while (0)
#else
#define debug(x)
#define debugVect(v)
#endif

class Allocator {
    int n;
    vector<int> mem;
    unordered_map<int, vector<int>> hash;
public:
    Allocator(int n) {
        this->n = n;
        mem.resize(n, 0);
    }
    
    int allocate(int size, int mID) {
        debug(size);
        debug(mID);
        if (size > n) return -1;
        int S = -1, E = -1;
        for (int i = 0; i < n; i++) {
            if (mem[i]) continue;
            for (int j = i; j <= n; j++) {
                if (j - i >= size) {
                    S = i;
                    E = j;
                    break;
                }
                if (j < n && mem[j]) {
                    i = j;
                    break;
                }
                if (S != -1) break;
            }
        }
        debug(S);
        if (S == -1) return -1;

        for (int i = S; i < E; i++) {
            mem[i] = mID;
            hash[mID].push_back(i);
        }
        debugVect(mem);
        return S;
    }
    
    int freeMemory(int mID) {
        debug(mID);
        if (hash.count(mID) == 0) return 0;
        for (int idx: hash[mID])
            mem[idx] = 0;
        int ret = hash[mID].size();
        hash.erase(mID);
        return ret;
    }
};

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->freeMemory(mID);
 */