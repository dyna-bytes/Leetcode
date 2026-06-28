
#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x);

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

void removeNode(Node* node) {
	Node* prev = node->prev;
	Node* next = node->next;

	if (prev) prev->next = next;
	if (next) next->prev = prev;
}

void insertNode(Node* node, Node* prev) {
	node->next = prev->next;
	if (prev->next) prev->next->prev = node;

	prev->next = node;
	node->prev = prev;
}

typedef struct {
    Node* head;
} Allocator;


Allocator* allocatorCreate(int n) {
    Allocator* obj = malloc(sizeof(*obj));
    Node* head = calloc(1, sizeof(*head));
    head->page.index = 0;
    head->page.size = n;
    head->page.mID = 0;
    obj->head = head;
    return obj;
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
	for (Node* curr = obj->head; curr; curr = curr->next) {
		if (curr->page.mID == 0 && curr->page.size >= size) { // empty & avail
			curr->page.mID = mID; // allocation
			if (curr->page.size == size) 
				return curr->page.index;
			
			Node* node = calloc(1, sizeof(*node));
			node->page.index = curr->page.index + size;
			node->page.size = curr->page.size - size;
			node->page.mID = 0;
			insertNode(node, curr); // separation
            curr->page.size = size;
			return curr->page.index;
		}
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
			removeNode(curr);
			free(curr);
			curr = prev;
		}

		Node* next = curr->next;
		if (next && next->page.mID == 0) {
			curr->page.size += next->page.size;
			removeNode(next);
			free(next);
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