/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#define swap(a, b) do { \
    int t = a; \
    a = b; \
    b = t; \
} while(0)
#define ROOT 1
#define HEAP_SIZE (1 << 14)
typedef struct {
    int arr[HEAP_SIZE];
    int size;
} heap;

heap* create() {
    heap* obj = malloc(sizeof(*obj));
    memset(obj->arr, 0, HEAP_SIZE * sizeof(int));
    obj->size = 0;
    return obj;
}

void heapify_up(heap* obj, int index) {
    int* arr = obj->arr;
    int curr = index;

    while (curr > ROOT) {
        int parent = curr / 2;
        if (arr[parent] <= arr[curr]) break;

        swap(arr[parent], arr[curr]);
        curr = parent;
    }
}

void heapify_down(heap* obj, int index) {
    int* arr = obj->arr;
    int* size = &obj->size;
    int curr = index;
    
    while (curr < (*size)) {
        int left = curr * 2;
        int right = curr * 2 + 1;
        int smallest = curr;

        if (left <= *size && arr[left] < arr[smallest])
            smallest = left;
        if (right <= *size && arr[right] < arr[smallest])
            smallest = right;

        if (smallest == curr) break;
        swap(arr[smallest], arr[curr]);
        curr = smallest;
    }
}

void push(heap* obj, int val) {
    int* arr = obj->arr;
    int* size = &obj->size;
    arr[++(*size)] = val;
    heapify_up(obj, (*size));
}

int is_empty(heap* obj) {
    return obj->size == 0;
}

int top(heap* obj) {
    if (is_empty(obj)) return -1;
    return obj->arr[ROOT];
}

void pop(heap* obj) {
    if (is_empty(obj)) return;

    int* arr = obj->arr;
    int* size = &obj->size;
    arr[ROOT] = arr[(*size)];
    (*size)--;
    heapify_down(obj, ROOT);
}


struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    heap* h = create();
    for (int i = 0; i < listsSize; i++) {
        struct ListNode* head = lists[i];
        for (struct ListNode* curr = head; curr; curr = curr->next)
            push(h, curr->val);
    }

    struct ListNode* ret = NULL;
    struct ListNode* curr, *prev = NULL;
    while (h->size) {
        curr = calloc(1, sizeof(*curr));
        curr->val = top(h);
        pop(h);

        if (prev)
            prev->next = curr;
        else
            ret = curr;
        prev = curr;
    }

    free(h);
    return ret;
}