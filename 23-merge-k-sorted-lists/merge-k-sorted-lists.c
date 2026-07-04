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
    Heap* obj = malloc(sizeof(*obj));
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->sz = 0;
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
    int* sz = &obj->sz;
    int curr = index;

    while (curr < (*sz)) {
        int left = curr * 2;
        int right = curr * 2 + 1;
        int smallest = curr;

        if (left <= *sz && arr[left] < arr[smallest])
            smallest = left;
        if (right <= *sz && arr[right] < arr[smallest])
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
    if (empty(obj)) return -1;
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
    Heap* heap = createHeap();
    for (int i = 0; i < listsSize; ++i) {
        for (struct ListNode* curr = lists[i]; curr; curr = curr->next)
            push(heap, curr->val);
    }

    struct ListNode* ret = NULL;
    struct ListNode* curr, *prev = NULL;
    while (!empty(heap)) {
        curr = calloc(1, sizeof(*curr));
        curr->val = top(heap);
        pop(heap);

        if (!ret) ret = curr;
        else prev->next = curr;
        prev = curr;
    }
    free(heap);
    return ret;
}