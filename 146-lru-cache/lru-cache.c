#define MAXN (10000 + 1)
typedef struct {
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
    Node* hash[MAXN]; // { key: node_t* }
} LRUCache;

void add_tail(Node* node, Node* tail) {
    Node* prev = tail->prev;
    prev->next = node;
    node->prev = prev;
    node->next = tail;
    tail->prev = node;
}

void del_list(Node* node) {
    Node* prev = node->prev;
    Node* next = node->next;
    prev->next = next;
    next->prev = prev;
    node->prev = node->next = NULL;
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
    Node** hash = obj->hash;
    if (!hash[key]) return -1;
    Node* node = hash[key];
    del_list(node);
    add_tail(node, obj->tail);
    return node->page.value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    Node** hash = obj->hash;
    if (lRUCacheGet(obj, key) != -1) {
        hash[key]->page.value = value;
        return;
    }

    int cap = obj->cap;
    int* sz = &obj->sz;
    if (++(*sz) > cap) {
        Node* evict = obj->head->next;
        hash[evict->page.key] = NULL;
        del_list(evict);
        free(evict);
        --(*sz);
    }

    Node* node = calloc(1, sizeof(*node));
    node->page.key = key;
    node->page.value = value;
    hash[key] = node;
    add_tail(node, obj->tail);
}

void lRUCacheFree(LRUCache* obj) {
    for (Node* curr = obj->head, *next; curr; curr = next) {
        next = curr->next;
        free(curr);
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