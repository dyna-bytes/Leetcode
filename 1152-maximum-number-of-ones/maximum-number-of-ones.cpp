#define debug(x) cout << #x << " is " << x << endl;
#define debugVect(v) do { \
    cout << #v << " is " << "|"; \
    for (auto e: v) cout << e << "|"; \
    cout << endl; \
} while (0)
#define debugVect2D(vv) do { \
    cout << #vv << " is " << endl; \
    for (auto v: vv) debugVect(v); \
} while (0)

class Solution {
    typedef pair<int, int> pii;
public:
    int maximumNumberOfOnes(int width, int height, int sideLength, int maxOnes) {
        priority_queue<int> pq;

        for (int y = 0; y < sideLength; y++)
            for (int x = 0; x < sideLength; x++) {
                int y_occur = height / sideLength + (y < height % sideLength);
                int x_occur = width / sideLength + (x < width % sideLength);
                pq.push(y_occur * x_occur);
            }
                
        int ones = 0;
        for (int i = 0; i < maxOnes && pq.size(); i++) {
            ones += pq.top();
            pq.pop();
        }
        return ones;
    }
};