#define MAXN (10000 + 1)
typedef struct page_t {
    int key;
    int value;
} Page;

typedef struct node_t {
    struct node_t* prev;
    struct node_t* next;
    Page page;
} Node;

typedef struct {
    int cap;
    int sz;
    Node* head;
    Node* tail;
    Node* lut[MAXN];    
} LRUCache;

void add_tail(Node* node, Node* tail) {
    tail->prev->next = node;
    node->prev = tail->prev;
    node->next = tail;
    tail->prev = node;
}

void del_node(Node* node) {
    Node* prev = node->prev;
    Node* next = node->next;
    prev->next = next;
    next->prev = prev;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* obj = calloc(1, sizeof(*obj));
    Node* head = calloc(1, sizeof(*head));
    Node* tail = calloc(1, sizeof(*tail));
    head->next = tail;
    tail->prev = head;
    obj->head = head;
    obj->tail = tail;
    obj->cap = capacity;
    return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
    Node** lut = obj->lut;
    if (lut[key] == NULL) return -1;

    Node* node = lut[key];
    del_node(node);
    add_tail(node, obj->tail);
    return node->page.value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    Node** lut = obj->lut;
    if (lRUCacheGet(obj, key) != -1) {
        lut[key]->page.value = value;
        return;
    }

    int cap = obj->cap;
    int* sz = &obj->sz;
    if (++(*sz) > cap) {
        Node* evict = obj->head->next;
        lut[evict->page.key] = NULL;
        del_node(evict);
        --(*sz);
    }

    Node* node = calloc(1, sizeof(*node));
    node->page.key = key;
    node->page.value = value;
    lut[key] = node;
    add_tail(node, obj->tail);
}

void lRUCacheFree(LRUCache* obj) {
    for (Node* node = obj->head, *next; node; node = next) {
        next = node->next;
        free(node);
    }
    free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/