
#define MAXKEY 100000 + 1
#define MAXFREQ 100000 + 1
// #define DBG
#ifdef DBG
#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x);
#else
#define debug(x)
#endif

typedef struct {
    int k, v, f;
} Page;

typedef struct node_t {
    Page page;
    struct node_t* prev;
    struct node_t* next;
    struct node_t* head;
    struct node_t* tail;
} Node;

void insertTail(Node* node, Node* tail) {
    debug(node->page.k);
    debug(node->page.v);
    
    node->head = tail->head;
    node->tail = tail;

    Node* prev = tail->prev;
    prev->next = node;
    node->prev = prev;

    node->next = tail;
    tail->prev = node;
}

void removeNode(Node* node) {
    debug(node->page.k);
    debug(node->page.v);

    Node* prev = node->prev;
    Node* next = node->next;
    prev->next = next;
    next->prev = prev;
}

typedef struct {
    Node** lut; // {key: Node*}
    Node** freq; // {freq: head}
    int* freq_sz; // {freq: int}
    int cap;
    int sz;
    int min_f;
} LFUCache;


LFUCache* lFUCacheCreate(int capacity) {
    LFUCache* obj = malloc(sizeof(*obj));
    Node** lut = (Node**)calloc(MAXKEY, sizeof(Node*));
    obj->lut = lut;

    Node** freq = (Node**)calloc(MAXFREQ, sizeof(Node*));
    for (int i = 0; i < MAXFREQ; ++i) {
        Node* head = calloc(1, sizeof(*head));
        Node* tail = calloc(1, sizeof(*tail));
        head->next = head->tail = tail;
        tail->prev = tail->head = head;

        freq[i] = head;
    }
    obj->freq = freq;

    int* freq_sz = calloc(MAXFREQ, sizeof(int));
    obj->freq_sz = freq_sz;

    obj->cap = capacity;
    obj->sz = 0;
    obj->min_f = 0;
    return obj;
}

int lFUCacheGet(LFUCache* obj, int key) {
    debug(key);
    Node** lut = obj->lut;
    if (lut[key] == NULL) return -1;

    Node* node = lut[key];
    Page* page = &node->page;
    int* k = &page->k, *v = &page->v, *f = &page->f;
    int* min_f = &obj->min_f;
    Node** freq = obj->freq;
    int* freq_sz = obj->freq_sz;

    removeNode(node);
    if (--freq_sz[*f] == 0 && *f == *min_f) 
        ++(*min_f);

    ++(*f);

    insertTail(node, freq[*f]->tail);
    ++freq_sz[*f];

    return *v;
}

void lFUCachePut(LFUCache* obj, int key, int value) {
    debug(key);
    debug(value);
    Node** lut = obj->lut;
    if (lut[key]) {
        lFUCacheGet(obj, key);
        lut[key]->page.v = value;
        return;
    }

    int* sz = &obj->sz;
    int cap = obj->cap;
    int* min_f = &obj->min_f;
    Node** freq = obj->freq;
    int* freq_sz = obj->freq_sz;

    if (++(*sz) > cap) {
        debug(*min_f);
        Node* victim = freq[*min_f]->next;
        Page* page = &victim->page;
        int* k = &page->k, *v = &page->v, *f = &page->f;

        removeNode(victim);
        --freq_sz[*f];

        lut[victim->page.k] = NULL;
        free(victim);
        --(*sz);
    }

    Node* node = calloc(1, sizeof(*node));
    node->page.k = key;
    node->page.v = value;
    node->page.f = *min_f = 1;
    insertTail(node, freq[*min_f]->tail);
    ++freq_sz[*min_f];
    lut[key] = node;
}

void lFUCacheFree(LFUCache* obj) {
    for (int i = 0; i < MAXFREQ; i++) {
        if (obj->freq[i]) {
            for (Node* curr = obj->freq[i], *next; curr; curr = next) {
                next = curr->next;
                free(curr);
            }
        }
    } 

    free(obj->freq);
    free(obj->freq_sz);
    free(obj->lut);
    free(obj);
}

/**
 * Your LFUCache struct will be instantiated and called as such:
 * LFUCache* obj = lFUCacheCreate(capacity);
 * int param_1 = lFUCacheGet(obj, key);
 
 * lFUCachePut(obj, key, value);
 
 * lFUCacheFree(obj);
*/