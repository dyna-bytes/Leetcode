
#define HASH_SIZE (2 << 12)
typedef struct page_t {
    int key;
    int val;
} Page;

typedef struct node_t {
    struct node_t* prev;
    struct node_t* next;
    Page page;
} Node;

typedef struct {
    struct node_t* heads[HASH_SIZE];
} MyHashMap;

void insert_node(Node** head, Node* curr) {
    if (*head == NULL) *head = curr;
    else {
        curr->next = *head;
        (*head)->prev = curr;
        *head = curr;
    }
}

void remove_node(Node** head, Node* curr) {
    Node* prev = curr->prev;
    Node* next = curr->next;
    if (prev) prev->next = next;
    else *head = next;

    if (next) next->prev = prev;
}


int hash(int key) {
    return (key % HASH_SIZE);
}

Node* find(MyHashMap* obj, int key) {
    int h = hash(key);
    Node* node = obj->heads[h];
    while (node) {
        if (node->page.key == key) return node;
        node = node->next;
    }
    return NULL;
}

MyHashMap* myHashMapCreate() {
    MyHashMap* obj = calloc(1, sizeof(*obj));
    memset(obj->heads, 0, sizeof(obj->heads));
    return obj;
}

void myHashMapPut(MyHashMap* obj, int key, int value) {
    Node* node = find(obj, key);
    if (node) {
        node->page.val = value;
        return;
    }

    node = calloc(1, sizeof(*node));
    node->page.key = key;
    node->page.val = value;
    int h = hash(key);
    insert_node(&obj->heads[h], node);
}

int myHashMapGet(MyHashMap* obj, int key) {
    Node* node = find(obj, key);
    if (!node) return -1;
    return node->page.val;
}

void myHashMapRemove(MyHashMap* obj, int key) {
    Node* node = find(obj, key);
    if (!node) return;

    int h = hash(key);
    remove_node(&obj->heads[h], node);
    free(node);
}

void myHashMapFree(MyHashMap* obj) {
    free(obj);
}

/**
 * Your MyHashMap struct will be instantiated and called as such:
 * MyHashMap* obj = myHashMapCreate();
 * myHashMapPut(obj, key, value);
 
 * int param_2 = myHashMapGet(obj, key);
 
 * myHashMapRemove(obj, key);
 
 * myHashMapFree(obj);
*/