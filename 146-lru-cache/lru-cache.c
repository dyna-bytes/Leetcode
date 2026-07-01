#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x);
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
    Node* lut[MAXN]; // {key: node*}
    Node* head;
    Node* tail;

    int cap;
    int sz;
} LRUCache;

void insertBack(Node* node, Node* tail) {
    tail->prev->next = node;
    node->prev = tail->prev;

    node->next = tail;
    tail->prev = node;
}

void removeNode(Node* node) {
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
    obj->sz = 0;
    return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
    Node** lut = obj->lut;
    if (lut[key] == NULL) return -1;
    Node* node = lut[key];
    removeNode(node);
    insertBack(node, obj->tail);
    return node->page.value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    Node** lut = obj->lut;
    if (lut[key]) {
        lRUCacheGet(obj, key);
        lut[key]->page.value = value;
        return;
    }

    int cap = obj->cap;
    int* sz = &obj->sz;
    Node* head = obj->head;
    Node* tail = obj->tail;
    if (++(*sz) > cap) {
        Node* evict = head->next;
        removeNode(evict);
        lut[evict->page.key] = NULL;
        --(*sz);
    }

    Node* node = calloc(1, sizeof(*node));
    node->page.key = key;
    node->page.value = value;
    lut[key] = node;
    insertBack(node, tail);
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