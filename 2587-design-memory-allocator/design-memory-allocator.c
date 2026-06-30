
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
    Node* free_bins[MAXN];
    Node* mID_map[MAXN];
} Allocator;

void insertToList(Node** head, Node* node) {
    node->list_next = *head;
    node->list_prev = NULL;
    if (*head) (*head)->list_prev = node;
    *head = node;
}

void removeFromList(Node** head, Node* node) {
    if (node->list_prev) node->list_prev->list_next = node->list_next;
    else *head = node->list_next;

    if (node->list_next) node->list_next->list_prev = node->list_prev;
    node->list_prev = node->list_next = NULL;
}

Allocator* allocatorCreate(int n) {
    Allocator* obj = calloc(1, sizeof(*obj));
    Node* head = calloc(1, sizeof(Node));
    head->page.index = 0;
    head->page.size = n;
    head->page.mID = 0;

    obj->head = head;
    insertToList(&obj->free_bins[n], head);
    return obj;
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
    Node* best_node = NULL;
    for (int s = size; s < MAXN; s++) {
        for (Node* curr = obj->free_bins[s]; curr; curr = curr->list_next) {
            if (!best_node || curr->page.index < best_node->page.index)
                best_node = curr;
        }
    }

    if (!best_node)	return -1;

    removeFromList(&obj->free_bins[best_node->page.size], best_node);

    if (best_node->page.size > size) {
        Node* split = calloc(1, sizeof(Node));
        split->page.index = best_node->page.index + size;
        split->page.size = best_node->page.size - size;
        split->page.mID = 0;

        split->next = best_node->next;
        split->prev = best_node;
        if (best_node->next) best_node->next->prev = split;
        best_node->next = split;

        insertToList(&obj->free_bins[split->page.size], split);
        best_node->page.size = size;
    }

    best_node->page.mID = mID;
    insertToList(&obj->mID_map[mID], best_node);
    return best_node->page.index;
}

int allocatorFreeMemory(Allocator* obj, int mID) {
	int sz = 0;
    for (Node* curr = obj->mID_map[mID], *next_target; curr; curr = next_target) {
        next_target = curr->list_next;

        removeFromList(&obj->mID_map[mID], curr);
        curr->page.mID = 0;
        sz += curr->page.size;

        Node* next = curr->next;
        if (next && next->page.mID == 0) {
            removeFromList(&obj->free_bins[next->page.size], next);
            curr->page.size += next->page.size;
            curr->next = next->next;
            if (next->next) next->next->prev = curr;
            free(next);
        }

        Node* prev = curr->prev;
        if (prev && prev->page.mID == 0) {
            removeFromList(&obj->free_bins[prev->page.size], prev);
            prev->page.size += curr->page.size;
            prev->next = curr->next;
            if (curr->next) curr->next->prev = prev;
            free(curr);
            curr = prev;
        }

        insertToList(&obj->free_bins[curr->page.size], curr);
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