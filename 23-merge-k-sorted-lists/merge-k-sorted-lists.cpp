/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (ListNode* listhead: lists) {
            for (ListNode* curr = listhead; curr; curr = curr->next)
                pq.push(curr->val);
        }

        ListNode* ret = nullptr, *curr = nullptr;
        while (pq.size()) {
            int val = pq.top(); pq.pop();
            ListNode* next = new ListNode(val);

            if (curr) {
                curr->next = next;
                curr = next;
            } else {
                ret = curr = next;
            }
        }
        return ret;
    }
};