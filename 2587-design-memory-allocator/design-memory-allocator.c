
#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x);

typedef struct {
    int index;
    int size;
    int mID;
} Page;

typedef struct node_t {
    Page page;
    struct node_t* prev;
    struct node_t* next;
} Node;

typedef struct {
    Node* head;
} Allocator;


Allocator* allocatorCreate(int n) {
    Allocator* obj = malloc(sizeof(*obj));
    Node* head = calloc(1, sizeof(*head));
    head->page.index = 0;
    head->page.size = n;
    head->page.mID = -1;
    obj->head = head;
    return obj;
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
    Node* head = obj->head;
    for (Node* curr = head; curr; curr = curr->next) {
        if (curr->page.mID != -1) continue;
        if (curr->page.size < size) continue;
        curr->page.mID = mID;
        Node* next = calloc(1, sizeof(*next));

        next->page.index = curr->page.index + size;
        next->page.size = curr->page.size - size;
        next->page.mID = -1;

        next->prev = curr;
        next->next = curr->next;
        if (curr->next)
            curr->next->prev = next;

        curr->next = next;
        curr->page.size = size;
        return curr->page.index;
    }
    return -1;
}

int allocatorFreeMemory(Allocator* obj, int mID) {
    int sz = 0;
    Node* head = obj->head;
    for (Node* curr = head; curr; curr = curr->next) {
        if (curr->page.mID == mID) {
            sz += curr->page.size;
            curr->page.mID = -1;
            Node* prev = curr->prev;
            Node* next = curr->next;

            if (prev && prev->page.mID == -1) {
                prev->page.size += curr->page.size;
                prev->next = next;
                if (next)
                    next->prev = prev;
                free(curr);
                curr = prev;
            }

            if (next && next->page.mID == -1) {
                curr->page.size += next->page.size;
                curr->next = next->next;
                if (next->next)
                    next->next->prev = curr;
                free(next);
            }
        }
    }
    return sz;
}

void allocatorFree(Allocator* obj) {
    Node* head = obj->head;
    for (Node* curr = head, *next; curr; curr = next) {
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