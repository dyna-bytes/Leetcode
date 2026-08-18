/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#define SWAP(t, a, b) do { \ 
    t tmp = a; \
    a = b; \
    b = tmp; \
} while (0)
#define ROOT 1
#define HEAP_SIZE (1 << 14)
typedef struct {
    int arr[HEAP_SIZE];
    int sz;
} Heap;

Heap* createHeap() {
    Heap* obj = calloc(1, sizeof(*obj));
    return obj;
}

void heapify_up(Heap* obj, int index) {
    int* arr = obj->arr;
    int curr = index;
    while (curr > ROOT) {
        int parent = curr / 2;
        if (arr[parent] <= arr[curr]) break;
        SWAP(int, arr[parent], arr[curr]);
        curr = parent;
    }
}

void heapify_down(Heap* obj, int index) {
    int* arr = obj->arr;
    int sz = obj->sz;
    int curr = index;

    while (curr < sz) {
        int left = curr * 2;
        int right = curr * 2 + 1;
        int smallest = curr;

        if (left <= sz && arr[left] < arr[smallest])
            smallest = left;
        if (right <= sz && arr[right] < arr[smallest])
            smallest = right;
        
        if (smallest == curr) break;
        SWAP(int, arr[smallest], arr[curr]);
        curr = smallest;
    }
}

void push(Heap* obj, int val) {
    int* arr = obj->arr;
    int* sz = &obj->sz;
    arr[++(*sz)] = val;
    heapify_up(obj, (*sz));
}

bool empty(Heap* obj) {
    return obj->sz == 0;
}

int top(Heap* obj) {
    if (empty(obj)) return INT_MIN;
    return obj->arr[ROOT];
}

void pop(Heap* obj) {
    if (empty(obj)) return;

    int* arr = obj->arr;
    int* sz = &obj->sz;
    arr[ROOT] = arr[*sz];
    --(*sz);
    heapify_down(obj, ROOT);
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;
    if (listsSize == 1) return lists[0];

    Heap* heap = createHeap();
    struct ListNode ret;
    struct ListNode* curr = &ret;
    bool pushed;
    do {
        pushed = false;
        for (int i = 0; i < listsSize; ++i) {
            struct ListNode* head = lists[i];
            if (!head) continue;
            push(heap, head->val);
            lists[i] = head->next;
            pushed = true;
        } 

        int val = top(heap);
        pop(heap);
        if (val == INT_MIN) continue;

        struct ListNode* node = calloc(1, sizeof(*node));
        node->val = val;
        curr->next = node;
        curr = node;
    } while (pushed || !empty(heap));
    free(heap);
    return ret.next;
}