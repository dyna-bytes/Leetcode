/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define HASH_SIZE (1 << 14)
#define LIST_SIZE (1 << 14)
#define UNDEFINED (INT_MIN)
typedef unsigned int u32;
typedef unsigned long long u64;
typedef struct {
    int head[HASH_SIZE];
    int key[LIST_SIZE];
    int val[LIST_SIZE];
    int next[LIST_SIZE];
    int prev[LIST_SIZE];
    int unused;
} HashMap;

int hash(int k) {
    return (k % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
}

void fill(void *s, void *e, int v) {
    for (u32* p = (u32 *)s; p < (u32 *)e; p++)
        *p = v;
}

HashMap* create() {
    HashMap* obj = malloc(sizeof(*obj));
    fill(obj->head, obj->head + HASH_SIZE, UNDEFINED);
    fill(obj->key, obj->key + LIST_SIZE, UNDEFINED);
    fill(obj->val, obj->val + LIST_SIZE, UNDEFINED);
    fill(obj->next, obj->next + LIST_SIZE, UNDEFINED);
    fill(obj->prev, obj->prev + LIST_SIZE, UNDEFINED);
    obj->unused = 0;
    return obj;
}

int find(HashMap* obj, int k) {
    int h = hash(k);
    int node = obj->head[h];
    while (node != UNDEFINED) {
        if (obj->key[node] == k) return node;
        node = obj->next[node];
    }
    return UNDEFINED;
}

void put(HashMap* obj, int k, int v) {
    int node = find(obj, k);
    if (node != UNDEFINED) {
        obj->val[node] = v;
        return;
    }

    int h = hash(k);
    obj->key[obj->unused] = k;
    obj->val[obj->unused] = v;
    if (obj->head[h] != UNDEFINED) {
        obj->next[obj->unused] = obj->head[h];
        obj->prev[obj->head[h]] = obj->unused;
    }
    obj->head[h] = obj->unused;

    obj->unused++;
}

int get(HashMap* obj, int k) {
    int node = find(obj, k);
    if (node == UNDEFINED) return UNDEFINED;
    return obj->val[node];
}

void erase(HashMap* obj, int k) {
    int node = find(obj, k);

    if (obj->prev[node] != UNDEFINED) obj->next[obj->prev[node]] = obj->next[node];
    if (obj->next[node] != UNDEFINED) obj->prev[obj->next[node]] = obj->prev[node];

    int h = hash(k);
    if (obj->head[h] == node)
        obj->head[h] = obj->next[node];
}
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int n = numsSize;
    *returnSize = 2;
    int* ret = calloc(*returnSize, sizeof(int));

    HashMap* map = create();
    for (int i = 0; i < n; i++) {
        int j = get(map, target - nums[i]);
        if (j != UNDEFINED) {
            ret[0] = j;
            ret[1] = i;
            return ret;
        }

        put(map, nums[i], i);
    }
    return NULL;
}