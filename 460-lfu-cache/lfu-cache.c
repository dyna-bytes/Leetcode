#define MAXKEY (100000 + 1)
#define MAXFREQ (100000 + 1)
#ifdef DBG
#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x);
#else
#define debug(x)
#endif
typedef struct {
    int key;
    int value;
    int freq;
} Page;

typedef struct node_t {
    struct node_t* prev;
    struct node_t* next;
    struct node_t* head;
    struct node_t* tail;
    Page page;
} Node;

typedef struct {
    int cap;
    int sz;
    int min_f;
    Node* freq[MAXFREQ];
    Node* cache[MAXKEY];    
} LFUCache;

void lazyAlloc(Node* freq[MAXFREQ], int key) {
    if (freq[key]) return;
    Node* head = calloc(1, sizeof(*head));
    Node* tail = calloc(1, sizeof(*tail));
    head->next = head->tail = tail;
    tail->prev = tail->head = head;
    freq[key] = head;
}

void insertTail(Node* node, Node* tail) {
    debug(node->page.value);
    Node* prev = tail->prev;
    prev->next = node;
    node->prev = prev;
    node->next = tail;
    tail->prev = node;

    node->head = tail->head;
    node->tail = tail;
}

void removeNode(Node* node) {
    debug(node->page.value);
    Node* prev = node->prev;
    Node* next = node->next;

    prev->next = next;
    next->prev = prev;
    node->prev = node->next = NULL;
}

bool listEmpty(Node* head) {
    Node* tail = head->tail;
    return (head->next == tail && tail->prev == head);
}

LFUCache* lFUCacheCreate(int capacity) {
    LFUCache* obj = calloc(1, sizeof(*obj));
    obj->cap = capacity;
    return obj;
}

int lFUCacheGet(LFUCache* obj, int key) {
    debug(key);
    Node** cache = obj->cache;
    Node** freq = obj->freq;
    int* min_f = &obj->min_f;
    if (cache[key] == NULL) return -1;

    Node* node = cache[key];
    Page* page = &node->page;
    int *k = &page->key, *v = &page->value, *f = &page->freq;
    removeNode(node);

    lazyAlloc(freq, *f);
    if (*f == *min_f && listEmpty(freq[*f])) ++(*min_f);
    ++(*f);

    lazyAlloc(freq, *f);
    insertTail(node, obj->freq[*f]->tail);
    return *v;
}

void lFUCachePut(LFUCache* obj, int key, int value) {
    debug(key);
    debug(value);
    Node** cache = obj->cache;
    Node** freq = obj->freq;
    int* min_f = &obj->min_f;
    int* sz = &obj->sz;
    int cap = obj->cap;
    if (cache[key]) {
        lFUCacheGet(obj, key);
        cache[key]->page.value = value;
        return;
    }

    if (++(*sz) > cap) {
        lazyAlloc(freq, *min_f);
        Node* evict = freq[*min_f]->next;
        removeNode(evict);
        cache[evict->page.key] = NULL;
        free(evict);
        --(*sz);
    }

    (*min_f) = 1;
    Node* node = calloc(1, sizeof(*node));
    node->page.key = key;
    node->page.value = value;
    node->page.freq = (*min_f);

    lazyAlloc(freq, *min_f);
    insertTail(node, freq[*min_f]->tail);
    cache[key] = node;
}

void lFUCacheFree(LFUCache* obj) {
    Node** freq = obj->freq;
    for (int i = 0; i < MAXFREQ; ++i) {
        if (freq[i] && freq[i]->tail) free(freq[i]->tail);
        if (freq[i]) free(freq[i]);
    }
    free(obj);
}

/**
 * Your LFUCache struct will be instantiated and called as such:
 * LFUCache* obj = lFUCacheCreate(capacity);
 * int param_1 = lFUCacheGet(obj, key);
 
 * lFUCachePut(obj, key, value);
 
 * lFUCacheFree(obj);
*/