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

        auto addListCarry = [&](ListNode* l, int c) {
            int sum = l->val + c;
            l->val = sum % 10;
            l->next = add(sum / 10, l->next, nullptr);
            return l;
        };

        if (!l2) 
            return addListCarry(l1, carry);

        if (!l1) 
            return addListCarry(l2, carry);

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