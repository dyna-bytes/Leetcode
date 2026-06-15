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
    ListNode** findMiddle(ListNode** head) {
        ListNode** slow = &(*head)->next;
        ListNode** fast = &(*head)->next;
        while ((*fast) && (*fast)->next && (*fast)->next->next) {
            slow = &(*slow)->next;
            fast = &(*fast)->next->next;
        }
        return slow;
    }
public:
    ListNode* deleteMiddle(ListNode* head) {
        ListNode** middle = findMiddle(&head);
        if (*middle == nullptr) return nullptr;

        *middle = (*middle)->next;
        return head;
    }
};