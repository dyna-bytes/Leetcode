class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
        int apples = accumulate(apple.begin(), apple.end(), 0);
        priority_queue<int> boxes(capacity.begin(), capacity.end());

        int cnt = 0;
        while (boxes.size()) {
            int box = boxes.top();
            boxes.pop();

            apples -= box;
            cnt++;

            if (apples <= 0) break;
        }
        return cnt;
    }
};