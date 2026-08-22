
#define MAXN (100000 + 1)

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
    Node* freqs[MAXN]; // { freq: node list }
    Node* cache[MAXN]; // { key: node* }
} LFUCache;

void insert_tail(Node* node, Node* tail) {
    Node* prev = tail->prev;
    prev->next = node;
    node->prev = prev;
    node->next = tail;
    tail->prev = node;
    node->head = tail->head;
    node->tail = tail;
}

void remove_node(Node* node) {
    Node* prev = node->prev;
    Node* next = node->next;
    prev->next = next;
    next->prev = prev;
    node->prev = node->next = node->head = node->tail = NULL;
}

bool list_empty(Node* tail) {
    Node* head = tail->head;
    return head->next == tail;
}

LFUCache* lFUCacheCreate(int capacity) {
    LFUCache* obj = calloc(1, sizeof(*obj));
    
    for (int i = 0; i < MAXN; ++i) {
        Node* head = calloc(1, sizeof(*head));
        Node* tail = calloc(1, sizeof(*tail));
        obj->freqs[i] = tail->head = tail->prev = head;
        insert_tail(head, tail);
    }

    obj->cap = capacity;
    return obj;
}

int lFUCacheGet(LFUCache* obj, int key) {
    Node** cache = obj->cache;
    Node** freqs = obj->freqs;
    if (cache[key] == NULL) return -1;

    Node* node = cache[key];
    int* min_f = &obj->min_f;
    int* f = &node->page.freq;
    remove_node(node);
    if ((*f == *min_f) && list_empty(freqs[*min_f]->tail)) ++(*min_f);
    ++(*f);
    insert_tail(node, freqs[*f]->tail);
    return node->page.value;
}

void lFUCachePut(LFUCache* obj, int key, int value) {
    Node** cache = obj->cache;
    Node** freqs = obj->freqs;
    if (lFUCacheGet(obj, key) != -1) {
        cache[key]->page.value = value;
        return;
    }

    int* min_f = &obj->min_f;
    int* sz = &obj->sz;
    int cap = obj->cap;
    if (++(*sz) > cap) {
        Node* evict = obj->freqs[*min_f]->next;
        cache[evict->page.key] = NULL;
        remove_node(evict);
        free(evict);
        --(*sz);
    }

    Node* node = calloc(1, sizeof(*node));
    node->page.key = key;
    node->page.value = value;
    node->page.freq = *min_f = 1;
    cache[key] = node;
    insert_tail(node, freqs[*min_f]->tail);
}

void lFUCacheFree(LFUCache* obj) {
    Node** freqs = obj->freqs;
    for (int i = 0; i < MAXN; ++i) {
        if (freqs[i] && freqs[i]->tail) free(freqs[i]->tail);
        if (freqs[i]) free(freqs[i]);
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