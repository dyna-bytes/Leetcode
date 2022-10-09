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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* curr = new ListNode(-1);
        ListNode* head = curr;

        int carry = 0;
        int sum = 0;
        while (l1 || l2 || carry ) {
            int add = carry + (l1 ? l1->val:0) + (l2 ? l2->val:0);
            sum = add % 10;
            carry = add / 10;

            ListNode* node = new ListNode(sum);
            curr->next = node;

            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
            curr = curr->next;
        }

        return head = head->next;
    }
};