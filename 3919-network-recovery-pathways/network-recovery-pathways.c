typedef long long ll;
typedef struct pair_t {
    ll first, second;
} Pair;

bool cmp(Pair l, Pair r) {
    return l.first < r.first;
}

#define SWAP(type, a, b) do { \
    type t = a; \
    a = b; \
    b = t; \
} while (0)
#define HEAP_SIZE (1 << 15)
#define ROOT 1
typedef struct {
    Pair arr[HEAP_SIZE];
    int sz;
} Heap;

Heap* createHeap() {
    Heap* obj = calloc(1, sizeof(*obj));
    return obj;
}

void heapify_up(Heap* obj, int index) {
    Pair* arr = obj->arr;
    int curr = index;
    while (curr > ROOT) {
        int parent = curr / 2;
        if (cmp(arr[parent], arr[curr])) break;
        SWAP(Pair, arr[parent], arr[curr]);
        curr = parent;
    }
}

void heapify_down(Heap* obj, int index) {
    Pair* arr = obj->arr;
    int* sz = &obj->sz;
    int curr = index;
    
    while (curr < (*sz)) {
        int left = curr * 2;
        int right = curr * 2 + 1;
        int smallest = curr;
        if (left <= (*sz) && cmp(arr[left], arr[smallest]))
            smallest = left;
        if (right <= (*sz) && cmp(arr[right], arr[smallest]))
            smallest = right;
        
        if (smallest == curr) break;
        SWAP(Pair, arr[smallest], arr[curr]);
        curr = smallest;
    }
}

bool is_empty(Heap* obj) {
    return obj->sz == 0;
}

Pair top(Heap* obj) {
    Pair err = {-1, -1};
    if (is_empty(obj)) return err;
    Pair *arr = obj->arr;
    return arr[ROOT];
}

void push(Heap* obj, Pair val) {
    Pair* arr = obj->arr;
    int* sz = &obj->sz;
    arr[++(*sz)] = val;
    heapify_up(obj, *sz);
}

void pop(Heap* obj) {
    if (is_empty(obj)) return;
    Pair* arr = obj->arr;
    int* sz = &obj->sz;
    arr[ROOT] = arr[*sz];
    --(*sz);
    heapify_down(obj, ROOT);
}

#define MAXN (int)(5 * 1e4 + 1)
#define MAXM (int)(1e5 + 1)

typedef struct {
    int v, w;
    int next;
} Edge;
int adj[MAXN]; // head
Edge edges_pool[MAXM];
int edge_cnt;
ll dist[MAXN];

void add_edge(int u, int v, int w) {
    edges_pool[edge_cnt].v = v;
    edges_pool[edge_cnt].w = w;
    edges_pool[edge_cnt].next = adj[u];
    adj[u] = edge_cnt++;
}

bool dijkstra(int threshold, ll k, int n) {
    Heap* heap = createHeap();
    for (int i = 0; i < n; ++i)
        dist[i] = LLONG_MAX;

    dist[0] = 0;
    Pair s = {0, 0};
    push(heap, s);

    while (!is_empty(heap)) {
        Pair curr = top(heap); pop(heap);
        int d = curr.first, u = curr.second;
        if (d > k) return false;
        if (u == n - 1) {
            free(heap);
            return true;
        }
        for (int e = adj[u]; e != -1; e = edges_pool[e].next) {
            int v = edges_pool[e].v, w = edges_pool[e].w;
            if (w < threshold) continue;
            if (dist[v] <= dist[u] + w) continue;
            dist[v] = dist[u] + w;
            Pair node = {dist[v], v};
            push(heap, node);
        }
    }
    free(heap);
    return false;
}

int findMaxPathScore(int** edges, int edgesSize, int* edgesColSize, bool* online, int onlineSize, long long k) {
    memset(adj, -1, sizeof(adj));
    edge_cnt = 0;
    int l = INT_MAX, r = 0;
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        if (!online[u] || !online[v]) continue;

        add_edge(u, v, w);
        l = MIN(l, w) - 1;
        r = MAX(r, w) + 1;
    }

    if (!dijkstra(l, k, onlineSize)) return -1;

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (dijkstra(mid, k, onlineSize)) l = mid;
        else r = mid;
    }
    return l;
}