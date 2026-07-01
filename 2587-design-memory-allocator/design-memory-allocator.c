
#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x);
#define MAXN 1001

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


Allocator* allocatorCreate(int n) {
    Allocator* obj = calloc(1, sizeof(*obj));
    Node* head = calloc(1, sizeof(*head));
    head->page.index = 0;
    head->page.size = n;
    head->page.mID = 0;
    obj->head = head;
    return obj;
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
    for (Node* curr = obj->head; curr; curr = curr->next) {
        if (curr->page.mID) continue;
        if (curr->page.size < size) continue;

        curr->page.mID = mID;
        if (curr->page.size > size) {
            Node* next = calloc(1, sizeof(*next));
            next->page.index = curr->page.index + size;
            next->page.size = curr->page.size - size;
            next->page.mID = 0;

            if (curr->next) curr->next->prev = next;
            next->next = curr->next;
            curr->next = next;
            next->prev = curr;
        }
        curr->page.size = size;
        return curr->page.index;
    }
    return -1;
}

int allocatorFreeMemory(Allocator* obj, int mID) {
    int sz = 0;
    for (Node* curr = obj->head; curr; curr = curr->next) {
        if (curr->page.mID != mID) continue;

        curr->page.mID = 0;
        sz += curr->page.size;

        Node* prev = curr->prev;
        if (prev && prev->page.mID == 0) {
            prev->page.size += curr->page.size;
            if (curr->next) curr->next->prev = prev;
            prev->next = curr->next;
            free(curr);
            curr = prev;
        }

        Node* next = curr->next;
        if (next && next->page.mID == 0) {
            curr->page.size += next->page.size;
            if (next->next) next->next->prev = curr;
            curr->next = next->next;
            free(next);
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