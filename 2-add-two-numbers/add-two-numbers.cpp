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
    ListNode* add(int carry, ListNode* l1, ListNode* l2) {
        if (!l1 && !l2) {
            if (!carry) return nullptr;

            ListNode* node = new ListNode(carry);
            return node;
        }

        if (!l2) {
            int sum = l1->val + carry;
            l1->val = sum % 10;
            l1->next = add(sum / 10, l1->next, nullptr);
            return l1;
        }

        if (!l1) {
            int sum = l2->val + carry;
            l2->val = sum % 10;
            l2->next = add(sum / 10, l2->next, nullptr);
            return l2;
        } 

        int sum = l1->val + l2->val + carry;
        l1->val = sum % 10;
        l1->next = add(sum / 10, l1->next, l2->next);
        return l1;
    }
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return add(0, l1, l2);
    }
};