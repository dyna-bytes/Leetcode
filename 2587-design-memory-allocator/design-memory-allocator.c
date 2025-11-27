
typedef struct {
    int index;
    int size;
    int mID;
} Page;

typedef struct node {
    Page page;
    struct node* prev;
    struct node* next;
} Node;

typedef struct {
    Node* head;
} Allocator;


Allocator* allocatorCreate(int n) {
    Allocator* obj = malloc(sizeof(*obj));
    Node* node = calloc(1, sizeof(*node));
    node->page.index = 0;
    node->page.size = n;
    node->page.mID = -1;

    obj->head = node;
    return obj;
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
    // printf("[%s](%d) %d \n", __func__, __LINE__, mID);
    Node* head = obj->head;

    for (Node* curr = head; curr; curr = curr->next) {
        if (curr->page.size < size || curr->page.mID != -1) continue;

        curr->page.mID = mID;
        if (curr->page.size == size)
            return curr->page.index;

        Node* next = calloc(1, sizeof(*next));
        next->page.size = curr->page.size - size;
        next->page.index = curr->page.index + size;
        next->page.mID = -1;

        next->prev = curr;
        next->next = curr->next;
        if (next->next)
            next->next->prev = next;

        curr->next = next;
        curr->page.size = size;
        return curr->page.index;
    }

    return -1;
}

int allocatorFreeMemory(Allocator* obj, int mID) {
    // printf("[%s](%d) %d \n", __func__, __LINE__, mID);
    int sz = 0;
    Node* head = obj->head;
    for (Node* curr = head; curr; curr = curr->next) {
        // printf("mID[%d] size[%d] index[%d]\n", 
        //     curr->page.mID, curr->page.size, curr->page.index);
        if (curr->page.mID != mID) continue;

        curr->page.mID = -1;
        sz += curr->page.size;

        Node* prev = curr->prev;
        Node* next = curr->next;

        if (prev && prev->page.mID == -1) {
            prev->page.size += curr->page.size;
            prev->next = next;

            if (next)
                next->prev = prev;

            curr = prev;
        }

        if (next && next->page.mID == -1) {
            curr->page.size += next->page.size;
            curr->next = next->next;
            if (next->next)
                next->next->prev = curr;
        }
    }

    return sz;
}

void allocatorFree(Allocator* obj) {
    Node* curr = obj->head;
    for (Node* next; curr; curr = next) {
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