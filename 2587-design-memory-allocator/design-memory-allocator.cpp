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
    vector<int> mem;

    int getChunk(int size) {
        for (int i = 0; i < mem.size(); i++) {
            if (mem[i]) continue;

            int neededSize = size;
            for (int j = i; j < mem.size(); j++) {
                if (mem[j]) {
                    i = j;
                    break;
                }
                
                if (--neededSize == 0)
                    return j - size + 1;
            }
        }
        return -1;
    }
    void markAllocated(int start, int size, int mID) {
        while (size--)
            mem[start++] = mID;
    }
public:
    Allocator(int n) {
        mem.resize(n, 0);
    }
    
    int allocate(int size, int mID) {
        int start = getChunk(size);
        if (start == -1) return -1;

        markAllocated(start, size, mID);
        return start;
    }
    
    int freeMemory(int mID) {
        int freed = 0;
        for (int i = 0; i < mem.size(); i++)
            if (mem[i] == mID) { 
                mem[i] = 0;
                freed++;
            }
        return freed;
    }
};

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->freeMemory(mID);
 */