#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x);
#define MAXK 10000 + 1

typedef struct {
    int key;
    int value;
} Page;

typedef struct node_t {
    Page page;
    struct node_t* prev;
    struct node_t* next;
} Node;

typedef struct {
    Node** lut;
    Node* head;
    Node* tail;
    int cap;
    int sz;
} LRUCache;

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* obj = malloc(sizeof(*obj));

    Node** lut = calloc(MAXK, sizeof(Node*));
    obj->lut = lut;

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

void removeNode(Node* node) {
    // debug(node->page.key);
    // debug(node->page.value);
    Node* prev = node->prev;
    Node* next = node->next;
    prev->next = next;
    next->prev = prev;
}

void insertBack(Node* node, Node* tail) {
    // debug(node->page.key);
    // debug(node->page.value);
    Node* prev = tail->prev;
    prev->next = node;
    node->prev = prev;

    tail->prev = node;
    node->next = tail;
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
    int* sz = &obj->sz;
    int cap = obj->cap;

    if (lut[key]) {
        Node* node = lut[key];
        node->page.value = value;
        lRUCacheGet(obj, key);
        return;
    }

    if (*sz >= cap) {
        Node* victim = obj->head->next;
        lut[victim->page.key] = NULL;
        removeNode(victim);
        free(victim);
        (*sz)--;
    }

    Node* node = malloc(sizeof(*node));
    node->page.key = key;
    node->page.value = value;
    insertBack(node, obj->tail);
    lut[key] = node;
    (*sz)++;
}

void lRUCacheFree(LRUCache* obj) {
    Node* head = obj->head;
    for (Node* curr = head, *next; curr; curr = next) {
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