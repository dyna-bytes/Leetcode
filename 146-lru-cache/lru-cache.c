
#define MAXKEY 10000 + 1
typedef struct {
    int key;
    int val;
} Page;

typedef struct node {
    Page page;
    struct node* prev;
    struct node* next;
} Node;

typedef struct {
    Node** lut; // { key: node* }

    int cap;

    Node* head;
    Node* tail;
    int list_size;
} LRUCache;

void removeNode(Node* node) {
    Node* prev = node->prev;
    Node* next = node->next;
    prev->next = next;
    next->prev = prev;
} 

void insertTail(Node* node, Node* tail) {
    Node* prev = tail->prev;
    prev->next = node;
    node->prev = prev;

    node->next = tail;
    tail->prev = node;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* obj = malloc(sizeof(*obj));
    
    Node** lut = (Node**)calloc(MAXKEY, sizeof(Node*));
    obj->lut = lut;

    obj->cap = capacity;

    Node* head = malloc(sizeof(*head));
    obj->head = head;

    Node* tail = malloc(sizeof(*tail));
    obj->tail = tail;

    head->prev = tail->next = NULL;
    head->next = tail;
    tail->prev = head;

    obj->list_size = 0;
    return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
    Node** lut = obj->lut;
    if (lut[key] == NULL)
        return -1;

    Node* node = lut[key];
    removeNode(node);
    insertTail(node, obj->tail);

    Page* page = &node->page;
    return page->val;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    Node** lut = obj->lut;
    if (lut[key]) {
        Node* node = lut[key];
        removeNode(node);
        insertTail(node, obj->tail);

        Page* page = &node->page;
        page->val = value;
        return;
    }

    int* size = &obj->list_size;
    if (++(*size) > obj->cap) {
        Node* head = obj->head;
        Node* node = head->next;
        removeNode(node);

        Page* page = &node->page;
        lut[page->key] = NULL;

        free(node);
        --(*size);
    }

    Node* node = malloc(sizeof(*node));
    node->prev = node->next = NULL;
    Page* page = &node->page;
    page->key = key;
    page->val = value;

    lut[key] = node;

    insertTail(node, obj->tail);
}

void lRUCacheFree(LRUCache* obj) {
    if (obj->lut)
        free(obj->lut);

    Node* head = obj->head;
    Node* tail = obj->tail;
    if (head && tail && obj->list_size) {
        for (Node* curr = head->next, *next; curr && curr != tail; curr = next) {
            next = curr->next;
            free(curr);
        }

        free(obj->head);
        free(obj->tail);
    }
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/