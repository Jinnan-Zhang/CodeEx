// * Q: https://leetcode.cn/problems/merge-two-sorted-lists/description/
#include <iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode *container = new ListNode(), *p = container;
    ListNode *p1 = list1, *p2 = list2;
    while (p1 != nullptr && p2 != nullptr) {
        if (p1->val < p2->val) {
            p->next = p1;
            p1 = p1->next;
        } else {
            p->next = p2;
            p2 = p2->next;
        }
        p = p->next;
    }
    if (p1 != nullptr) {
        p->next = p1;
    } else if (p2 != nullptr) {
        p->next = p2;
    }
    return container->next;
}
using namespace std;
int TwoSortedLinkList() {
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(2);
    l1->next->next = new ListNode(4);
    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);
    ListNode* l3 = mergeTwoLists(l1, l2);
    while (l3 != nullptr) {
        cout << l3->val << endl;
        l3 = l3->next;
    }

    return 0;
}