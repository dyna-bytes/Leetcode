typedef unsigned int u32;
typedef unsigned long long u64;
#define HASH_SIZE (2 << 12)
#define LIST_SIZE (2 << 12)

typedef struct {
    int head[HASH_SIZE];
    int key[LIST_SIZE];
    int val[LIST_SIZE];
    int next[LIST_SIZE];
    int prev[LIST_SIZE];
    int unused;
} MyHashMap;

u32 hash(int k) {
    return (k % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
}

void fill(void* start, void* end, int v) {
    char* s_ptr = start;
    char* e_ptr = end;
    for (char* ptr = s_ptr; ptr < e_ptr; ptr++)
        *ptr = v;
}

int find(MyHashMap* obj, int k) {
    int h = hash(k);
    int node = obj->head[h];
    while (node != -1) {
        if (obj->key[node] == k) return node;
        node = obj->next[node];
    }
    return -1;
}

MyHashMap* myHashMapCreate() {
    MyHashMap* obj = calloc(1, sizeof(*obj));
    fill(obj->head, obj->head + HASH_SIZE, -1);
    fill(obj->key, obj->key + LIST_SIZE, -1);
    fill(obj->val, obj->val + LIST_SIZE, -1);
    fill(obj->next, obj->next + LIST_SIZE, -1);
    fill(obj->prev, obj->prev + LIST_SIZE, -1);
    obj->unused = 0;
    return obj;
}

void myHashMapPut(MyHashMap* obj, int k, int v) {
    int node = find(obj, k);
    if (node != -1) {
        obj->val[node] = v;
        return;
    }

    int h = hash(k);
    int* head = obj->head;
    int* key = obj->key;
    int* val = obj->val;
    int* next = obj->next;
    int* prev = obj->prev;
    int* unused = &obj->unused;
    
    key[*unused] = k;
    val[*unused] = v;

    if (head[h] != -1) {
        next[*unused] = head[h];
        prev[head[h]] = *unused;
    }
    head[h] = *unused;
    (*unused)++;
}

int myHashMapGet(MyHashMap* obj, int k) {
    int node = find(obj, k);
    if (node == -1) return -1;

    return obj->val[node];
}

void myHashMapRemove(MyHashMap* obj, int k) {
    int node = find(obj, k);
    if (node == -1) return;

    int h = hash(k);
    int* head = obj->head;
    int* next = obj->next;
    int* prev = obj->prev;
    
    if (prev[node] != -1) next[prev[node]] = next[node];
    if (next[node] != -1) prev[next[node]] = prev[node];

    if (head[h] == node) head[h] = next[node];
}

void myHashMapFree(MyHashMap* obj) {
    
}

/**
 * Your MyHashMap struct will be instantiated and called as such:
 * MyHashMap* obj = myHashMapCreate();
 * myHashMapPut(obj, key, value);
 
 * int param_2 = myHashMapGet(obj, key);
 
 * myHashMapRemove(obj, key);
 
 * myHashMapFree(obj);
*/