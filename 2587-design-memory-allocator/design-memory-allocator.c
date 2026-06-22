
#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x);
#define MAXN (1000 + 5)
typedef struct {
    int n;
    int mem[MAXN];
} Allocator;


Allocator* allocatorCreate(int n) {
    Allocator* obj = malloc(sizeof(*obj));
    obj->n = n;
    memset(obj->mem, 0, sizeof(obj->mem));
    return obj;
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
    int n = obj->n;
    int* mem = obj->mem;
    for (int s = 0, e; s + size <= n; ) {
        bool find = true;
        for (e = s; e < s + size; e++) {
            if (mem[e]) {
                find = false;
                break;
            }
        }

        if (find) {
            for (int e = s; e < s + size; e++)
                mem[e] = mID;
            return s;
        }
        
        s = e + 1;
    }
    return -1;
}

int allocatorFreeMemory(Allocator* obj, int mID) {
    int ret = 0;
    int n = obj->n;
    int* mem = obj->mem;
    for (int i = 0; i < n; i++) {
        if (mem[i] == mID) {
            mem[i] = 0;
            ret++;
        }
    }
    return ret;
}

void allocatorFree(Allocator* obj) {
    
}

/**
 * Your Allocator struct will be instantiated and called as such:
 * Allocator* obj = allocatorCreate(n);
 * int param_1 = allocatorAllocate(obj, size, mID);
 
 * int param_2 = allocatorFreeMemory(obj, mID);
 
 * allocatorFree(obj);
*/