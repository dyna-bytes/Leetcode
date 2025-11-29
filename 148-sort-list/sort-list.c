/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct ListNode LN;
#define NEXT(p) ((p)->next)
#define VAL(p) ((p)->val)

LN* split(LN* head) {
    LN* slow = head;
    LN* fast = head;
    while (fast && NEXT(fast)) {
        fast = NEXT(NEXT(fast));
        if (fast)
            slow = NEXT(slow);
    }
    LN* next = NEXT(slow);
    NEXT(slow) = NULL;
    return next;
}

LN* merge(LN* left, LN* right) {
    if (!left) return right;
    if (!right) return left;

    if (VAL(left) < VAL(right)) {
        NEXT(left) = merge(NEXT(left), right);
        return left;
    } else {
        NEXT(right) = merge(left, NEXT(right));
        return right;
    }
}

LN* mergesort(LN* head) {
    if (!head || !NEXT(head)) return head;

    LN* s = head;
    LN* m = split(s);

    s = mergesort(s);
    m = mergesort(m);

    return merge(s, m);
}


struct ListNode* sortList(struct ListNode* head) {
    return mergesort(head);
}