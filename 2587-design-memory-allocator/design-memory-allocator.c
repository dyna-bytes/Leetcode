
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
    struct node_t* list_prev;
    struct node_t* list_next;
    Page page;
} Node;

typedef struct {
    Node* head;
    Node* free_lists[MAXN]; // { size: node list }
    Node* alloc_lists[MAXN]; // { mID: node list }
} Allocator;

void insertToList(Node** head, Node* node) {
    node->list_next = (*head);
    node->list_prev = NULL;
    if (*head) (*head)->list_prev = node;
    (*head) = node;
}

void removeFromList(Node** head, Node* node) {
    if (node->list_prev) node->list_prev->list_next = node->list_next;
    else (*head) = node->list_next;

    if (node->list_next) node->list_next->list_prev = node->list_prev;
    node->list_prev = node->list_next = NULL;
}

Allocator* allocatorCreate(int n) {
    Allocator* obj = calloc(1, sizeof(*obj));
    Node* head = calloc(1, sizeof(*head));
    head->page.index = 0;
    head->page.size = n;
    head->page.mID = 0;
    insertToList(&obj->free_lists[n], head);
    obj->head = head;
    return obj;
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
    Node* best = NULL;
    for (int sz = size; sz < MAXN; ++sz) {
        for (Node* curr = obj->free_lists[sz]; curr; curr = curr->list_next) 
            if (!best || best->page.index > curr->page.index)
                best = curr;
    }

    if (!best) return -1;
    removeFromList(&obj->free_lists[best->page.size], best);

    if (best->page.size > size) {
        Node* split = calloc(1, sizeof(*split));
        split->page.index = best->page.index + size;
        split->page.size = best->page.size - size;
        split->page.mID = 0;

        split->next = best->next;
        split->prev = best;
        if (best->next) best->next->prev = split;
        best->next = split;
        insertToList(&obj->free_lists[split->page.size], split);
    }

    best->page.size = size;
    best->page.mID = mID;
    insertToList(&obj->alloc_lists[mID], best);
    return best->page.index;
}

int allocatorFreeMemory(Allocator* obj, int mID) {
    int sz = 0;
    for (Node* curr = obj->alloc_lists[mID], *list_next; curr; curr = list_next) {
        list_next = curr->list_next;
        removeFromList(&obj->alloc_lists[mID], curr);
        curr->page.mID = 0;
        sz += curr->page.size;

        Node* prev = curr->prev;
        if (prev && prev->page.mID == 0) {
            removeFromList(&obj->free_lists[prev->page.size], prev);
            prev->page.size += curr->page.size;
            prev->next = curr->next;
            if (curr->next) curr->next->prev = prev;
            free(curr);
            curr = prev;
        }

        Node* next = curr->next;
        if (next && next->page.mID == 0) {
            removeFromList(&obj->free_lists[next->page.size], next);
            curr->page.size += next->page.size;
            curr->next = next->next;
            if (next->next) next->next->prev = curr;
            free(next);
        }
        insertToList(&obj->free_lists[curr->page.size], curr);
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