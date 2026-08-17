
#define MAXN 1001
typedef struct page_t {
    int index;
    int size;
    int mID;
} Page;

typedef struct node_t {
    struct node_t* phys_prev;
    struct node_t* phys_next;
    struct node_t* list_prev;
    struct node_t* list_next;
    Page page;
} Node;

typedef struct {
    Node* head;
    Node* free_lists[MAXN];
    Node* alloc_lists[MAXN];
} Allocator;

void add_list(Node** head, Node* node) {
    if (*head) (*head)->list_prev = node;
    node->list_next = (*head);
    node->list_prev = NULL;
    (*head) = node;
}

void del_list(Node** head, Node* node) {
    if (node->list_prev) node->list_prev->list_next = node->list_next;
    else (*head) = node->list_next;

    if (node->list_next) node->list_next->list_prev = node->list_prev;
    node->list_prev = node->list_next = NULL;
}

void add_phys(Node* node, Node* phys_prev) {
    if (phys_prev->phys_next) phys_prev->phys_next->phys_prev = node;
    node->phys_next = phys_prev->phys_next;
    phys_prev->phys_next = node;
    node->phys_prev = phys_prev;
}

void del_phys(Node* node) {
    Node* phys_prev = node->phys_prev;
    Node* phys_next = node->phys_next;
    if (phys_prev) phys_prev->phys_next = phys_next;
    if (phys_next) phys_next->phys_prev = phys_prev;
    node->phys_next = node->phys_prev = NULL;
}

Allocator* allocatorCreate(int n) {
    Allocator* obj = calloc(1, sizeof(*obj));
    Node* head = calloc(1, sizeof(*head));
    head->page.size = n;
    obj->head = head;
    add_list(&obj->free_lists[n], head);
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
    del_list(&obj->free_lists[best->page.size], best);

    if (best->page.size > size) {
        Node* split = calloc(1, sizeof(*split));
        split->page.index = best->page.index + size;
        split->page.size = best->page.size - size;
        add_phys(split, best);
        add_list(&obj->free_lists[split->page.size], split);
        best->page.size = size;
    }

    best->page.mID = mID;
    add_list(&obj->alloc_lists[mID], best);
    return best->page.index;
}

int allocatorFreeMemory(Allocator* obj, int mID) {
    int sz = 0;
    for (Node* curr = obj->alloc_lists[mID], *list_next; curr; curr = list_next) {
        list_next = curr->list_next;
        del_list(&obj->alloc_lists[mID], curr);
        sz += curr->page.size;
        curr->page.mID = 0;

        Node* phys_prev = curr->phys_prev;
        if (phys_prev && phys_prev->page.mID == 0) {
            del_list(&obj->free_lists[phys_prev->page.size], phys_prev);
            phys_prev->page.size += curr->page.size;
            del_phys(curr);
            free(curr);
            curr = phys_prev;
        }

        Node* phys_next = curr->phys_next;
        if (phys_next && phys_next->page.mID == 0) {
            del_list(&obj->free_lists[phys_next->page.size], phys_next);
            curr->page.size += phys_next->page.size;
            del_phys(phys_next);
            free(phys_next);
        }
        add_list(&obj->free_lists[curr->page.size], curr);
    }
    return sz;
}

void allocatorFree(Allocator* obj) {
    for (Node* curr = obj->head, *phys_next; curr; curr = phys_next) {
        phys_next = curr->phys_next;
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