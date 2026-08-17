#define MAXKEY (100000 + 1)
#define MAXFREQ (100000 + 1)

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
    Node* lut[MAXKEY];    
} LFUCache;

void insertTail(Node* node, Node* tail) {
    Node* prev = tail->prev;
    prev->next = node;
    node->prev = prev;
    node->next = tail;
    tail->prev = node;

    node->head = tail->head;
    node->tail = tail;
}

void removeNode(Node* node) {
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
    for (int i = 0; i < MAXFREQ; ++i) {
        Node* head = calloc(1, sizeof(*head));
        Node* tail = calloc(1, sizeof(*tail));
        head->next = head->tail = tail;
        tail->prev = tail->head = head;
        obj->freq[i] = head;
    }
    return obj;
}

int lFUCacheGet(LFUCache* obj, int key) {
    Node** lut = obj->lut;
    Node** freq = obj->freq;
    int* min_f = &obj->min_f;
    if (lut[key] == NULL) return -1;

    Node* node = lut[key];
    Page* page = &node->page;
    int *k = &page->key, *v = &page->value, *f = &page->freq;
    removeNode(node);

    if (*f == *min_f && listEmpty(freq[*f])) ++(*min_f);
    ++(*f);
    insertTail(node, freq[*f]->tail);
    return *v;
}

void lFUCachePut(LFUCache* obj, int key, int value) {
    Node** lut = obj->lut;
    Node** freq = obj->freq;
    int* min_f = &obj->min_f;
    int* sz = &obj->sz;
    int cap = obj->cap;
    if (lFUCacheGet(obj, key) != -1) {
        lut[key]->page.value = value;
        return;
    }

    if (++(*sz) > cap) {
        Node* evict = freq[*min_f]->next;
        removeNode(evict);
        lut[evict->page.key] = NULL;
        free(evict);
        --(*sz);
    }

    (*min_f) = 1;
    Node* node = calloc(1, sizeof(*node));
    node->page.key = key;
    node->page.value = value;
    node->page.freq = *min_f;

    insertTail(node, freq[*min_f]->tail);
    lut[key] = node;
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