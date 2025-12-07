/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#define HASH_SIZE (1 << 12)
#define LIST_SIZE (1 << 12)
#define UNDEF INT_MIN

typedef struct {
    int head[HASH_SIZE];

    int key[LIST_SIZE];
    int val[LIST_SIZE];
    int prev[LIST_SIZE];
    int next[LIST_SIZE];

    int unused;
} hash_map;

hash_map* create() {
    hash_map* obj = malloc(sizeof(*obj));

    memset(obj->head, -1, sizeof(obj->head));
    memset(obj->key, -1, sizeof(obj->key));
    memset(obj->val, -1, sizeof(obj->val));
    memset(obj->prev, -1, sizeof(obj->prev));
    memset(obj->next, -1, sizeof(obj->next));

    obj->unused = 0;
    return obj;
}

int hash(int k) {
    return ((k % HASH_SIZE) + HASH_SIZE) % HASH_SIZE;
}

int find(hash_map* obj, int k) {
    int h = hash(k);

    int node = obj->head[h];
    while (node != -1) {
        if (obj->key[node] == k) return node;
        node = obj->next[node];
    }    
    return -1;
}

int get(hash_map* obj, int k) {
    int node = find(obj, k);
    if (node == -1) return UNDEF;
    return obj->val[node];
}

void put(hash_map* obj, int k, int v) {
    int node = find(obj, k);
    if (node != -1) {
        obj->val[node] = v;
        return;
    }

    int h = hash(k);
    int* head = obj->head;
    int* key = obj->key;
    int* val = obj->val;
    int* prev = obj->prev;
    int* next = obj->next;
    int* unused = &obj->unused;

    key[*unused] = k;
    val[*unused] = v;

    if (head[h] != -1) {
        next[*unused] = head[h];
        prev[head[h]] = *unused;
    }
    head[h] = *unused;
    (*unused)++;
} 

void erase(hash_map* obj, int k) {
    int node = find(obj, k);
    if (node == -1) return;

    int* head = obj->head;
    int* prev = obj->prev;
    int* next = obj->next;
    int h = hash(k);
    if (prev[node] != -1) next[prev[node]] = next[node];
    if (next[node] != -1) prev[next[node]] = prev[node];

    if (head[h] == node) head[h] = next[node];
}

int cmp(const void* l, const void* r) {
    return (*(int*)l) - (*(int*)r);
}
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int n = numsSize;
    hash_map* visited = create();

    qsort(nums, n, sizeof(int), cmp);

    *returnSize = 0;
    int** ret = calloc(n * n, sizeof(int*));
    *returnColumnSizes = calloc(n * n, sizeof(int));
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1, k = n - 1; j < k; ) {
            int eq = nums[i] + nums[j] + nums[k];
            
            if (eq < 0) j++;
            else if (eq > 0) k--;
            else if (find(visited, nums[j]) != -1 && get(visited, nums[j]) == nums[i]) j++;
            else {
                int* arr = calloc(3, sizeof(int));
                arr[0] = nums[i];
                arr[1] = nums[j];
                arr[2] = nums[k];
                ret[(*returnSize)] = arr;

                (*returnColumnSizes)[(*returnSize)] = 3;
                (*returnSize)++;

                put(visited, nums[j], nums[i]);
                j++, k--;
            } 
        }
    }

    return ret;
}