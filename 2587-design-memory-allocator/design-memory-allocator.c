
typedef struct {
    int index;
    int size;
    int mID;
} Page;

typedef struct node_t {
    struct node_t* prev;
    struct node_t* next;
    Page page;
} Node;

typedef struct {
    Node* head;    
} Allocator;

void insertNode(Node* node, Node* prev) {
    if (prev->next) prev->next->prev = node;
    node->next = prev->next;

    prev->next = node;
    node->prev = prev;
}

void removeNode(Node* node) {
    Node* prev = node->prev;
    Node* next = node->next;
    if (prev) prev->next = next;
    if (next) next->prev = prev;
}

Allocator* allocatorCreate(int n) {
    Allocator* obj = calloc(1, sizeof(*obj));
    Node* head = calloc(1, sizeof(*head));
    head->page.size = n;
    obj->head = head;
    return obj;
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
    for (Node* curr = obj->head; curr; curr = curr->next) {
        if (curr->page.mID) continue;
        if (curr->page.size < size) continue;

        if (curr->page.size > size) {
            Node* next = calloc(1, sizeof(*next));
            next->page.index = curr->page.index + size;
            next->page.size = curr->page.size - size;
            next->page.mID = 0;
            insertNode(next, curr);
            curr->page.size = size;
        }

        curr->page.mID = mID;
        return curr->page.index;
    }
    return -1;
}

int allocatorFreeMemory(Allocator* obj, int mID) {
    int sz = 0;
    for (Node* curr = obj->head; curr; curr = curr->next) {
        if (curr->page.mID != mID) continue;

        sz += curr->page.size;
        curr->page.mID = 0;
        
        Node* prev = curr->prev;
        if (prev && prev->page.mID == 0) {
            prev->page.size += curr->page.size;
            removeNode(curr);
            curr = prev;
        }

        Node* next = curr->next;
        if (next && next->page.mID == 0) {
            curr->page.size += next->page.size;
            removeNode(next);
        }
    }
    return sz;
}

void allocatorFree(Allocator* obj) {
    for (Node* curr = obj->head, *next; curr; curr = next) {
        next = curr->next;
        free(curr);
    }
    free(obj);
}

/**
 * Your Allocator struct will be instantiated and called as such:
 * Allocator* obj = allocatorCreate(n);
 * int param_1 = allocatorAllocate(obj, size, mID);
 
 * int param_2 = allocatorFreeMemory(obj, mID);
 
 * allocatorFree(obj);
*/