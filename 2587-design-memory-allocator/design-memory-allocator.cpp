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
    typedef pair<int, int> pii;
    unordered_map<int, vector<pii>> alloc; // { mID, vector{ {start, size} } }
    map<int, int> avail; // { start, size }

public:
    Allocator(int n) {
        avail.insert({ 0, n });
    }
    
    int allocate(int size, int mID) {
        for (auto it = avail.begin(); it != avail.end(); ++it) {
            auto [i, i_size] = *it;
            if (i_size < size) continue;
            
            alloc[mID].push_back({ i, size });
            avail.erase(it);
            if (i_size > size)
                avail.insert({ i + size, i_size - size });
            return i;
        }
        return -1;
    }
    
    int freeMemory(int mID) {
        int freed = 0;
        if (alloc.count(mID) == 0 || alloc[mID].size() == 0) return 0;

        for (auto [i, i_size]: alloc[mID]) {
            avail[i] = i_size;
            
            auto it = avail.find(i);
            if (it != avail.begin()) {
                auto [prv, prv_size] = *prev(it);
                if (prv + prv_size == i) {
                    avail[prv] += i_size;
                    it = prev(avail.erase(it));
                }
            }

            if (next(it) != avail.end()) {
                auto [nxt, nxt_size] = *next(it);
                if (i + i_size == nxt) {
                    it->second += nxt_size;
                    avail.erase(nxt);
                }
            }

            freed += i_size;
        }
        alloc.erase(mID);
        return freed;
    }
};

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->freeMemory(mID);
 */