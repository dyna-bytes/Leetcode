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
    ListNode* reverse(ListNode* curr, ListNode *prev, ListNode* end) {
        auto next = curr->next;
        curr->next = prev;
        if (curr == end) return curr;

        auto ret = reverse(next, curr, end);
        return ret;
    }
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        int cnt = 1;
        ListNode* prev = NULL, *start, * end;
        for (auto curr = head; curr; curr = curr->next) {
            if (cnt == left - 1) prev = curr;
            if (cnt == left) start = curr;
            if (cnt == right) end = curr;
            cnt++;
        }

        auto ret = reverse(start, end->next, end);
        if (left > 1) prev->next = ret;
        else if (left == 1) head = ret;
        return head;
    }
};