#define MAXKEY 100000 + 1
#define MAXFREQ 100000 + 1

typedef struct {
    int k;
    int v;
    int f;
} Page;

typedef struct node {
    Page page;
    struct node* prev;
    struct node* next;
    struct node* head;
    struct node* tail;
} Node;

void removeNode(Node* node) {
    Node* prev = node->prev;
    Node* next = node->next;

    prev->next = next;
    next->prev = prev;

    // printf("[%s] node val %d\n", __func__, node->page.v);
    // printf("[%s] prev val %d\n", __func__, node->prev->page.v);
    // printf("[%s] next val %d\n", __func__, node->next->page.v);
}

void insertTail(Node* node, Node* tail) {
    Node* prev = tail->prev;

    prev->next = node;
    node->prev = prev;

    node->next = tail;
    tail->prev = node;

    node->head = tail->head;
    node->tail = tail;

    // printf("[%s] node val %d\n", __func__, node->page.v);
    // printf("[%s] prev val %d\n", __func__, node->prev->page.v);
    // printf("[%s] next val %d\n", __func__, node->next->page.v);
}

typedef struct {
    int size;
    int cap;
    int minf;

    Node* freq[MAXFREQ]; // { freq: head }
    int freqsize[MAXFREQ];
    Node* lut[MAXKEY]; // { key: node* }
} LFUCache;

LFUCache* lFUCacheCreate(int capacity) {
    LFUCache* obj = calloc(1, sizeof(*obj));

    obj->cap = capacity;
    obj->minf = 1;

    Node** freq = obj->freq;
    int* freqsize = obj->freqsize;
    for (int i = 0; i < MAXFREQ; i++) {
        Node* head = calloc(1, sizeof(Node));
        Node* tail = calloc(1, sizeof(Node));
        head->next = head->tail = tail;
        tail->prev = tail->head = head;

        head->page.v = tail->page.v = -i;

        freq[i] = head;
        freqsize[i] = 0;
    }

    return obj;
}

int lFUCacheGet(LFUCache* obj, int key) {
    Node** lut = obj->lut;
    if (lut[key] == NULL) 
        return -1;

    Node* node = lut[key];
    Page* page = &node->page;
    int* f = &page->f;
    int* v = &page->v;

    Node** freq = obj->freq;
    int* freqsize = obj->freqsize;
    int* minf = &obj->minf;

    removeNode(node);
    if (--freqsize[*f] == 0 && *f == *minf)
        ++(*minf);

    ++(*f);
    insertTail(node, freq[*f]->tail);
    ++(freqsize[*f]);
    return *v;
}

void lFUCachePut(LFUCache* obj, int key, int value) {
    Node** lut = obj->lut;
    Node** freq = obj->freq;
    int* freqsize = obj->freqsize;
    int* minf = &obj->minf;

    if (lut[key]) {
        Node* node = lut[key];
        Page* page = &node->page;
        int* k = &page->k, *v = &page->v, *f = &page->f;
        
        assert(*k == key);
        *v = value;
        removeNode(node);
        if (--freqsize[*f] == 0 && *f == *minf)
            ++(*minf);

        ++(*f);
        insertTail(node, freq[*f]->tail);
        ++(freqsize[*f]);

        return;
    }

    int* size = &obj->size;
    int cap = obj->cap;
    if (++(*size) > cap) {
        Node* head = freq[*minf];
        Node* node = head->next;
        Page* page = &node->page;
        int* k = &page->k, *v = &page->v, *f = &page->f;

        lut[*k] = NULL;
        removeNode(node);
        if (--freqsize[*f] == 0 && *f == *minf)
            ++(*minf);
        free(node);
        --(*size);
    }

    Node* node = calloc(1, sizeof(*node));
    Page* page = &node->page;
    page->k = key, page->v = value, page->f = 1;
    insertTail(node, freq[1]->tail);
    ++(freqsize[1]);
    lut[key] = node;

    *minf = 1;
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
}

/**
 * Your LFUCache struct will be instantiated and called as such:
 * LFUCache* obj = lFUCacheCreate(capacity);
 * int param_1 = lFUCacheGet(obj, key);
 
 * lFUCachePut(obj, key, value);
 
 * lFUCacheFree(obj);
*/