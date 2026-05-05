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
    int getSize(ListNode* head) {
        int sz = 0;
        for (auto curr = head; curr; curr = curr->next)
            sz++;
        return sz;
    }
    ListNode* getKth(ListNode* head, int k) {
        int n = 0;
        for (auto curr = head; curr; curr = curr->next)
            if (n++ == k) return curr;
        return NULL;
    }
public:
    ListNode* rotateRight(ListNode* head, int k) {
        int N = getSize(head);
        if (N <= 1) return head;
        k %= N;

        auto brk = getKth(head, N - 1 - k);
        auto tail = getKth(head, N - 1);

        tail->next = head;
        head = brk->next;
        brk->next = nullptr;
        return head;
    }
};