// * Q: https://leetcode.cn/problems/merge-k-sorted-lists/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* container = new ListNode();
    container->next = head;
    ListNode *p1 = container, *p2 = container;
    for (int i = 0; i < n + 1; i++) {
        p1 = p1->next;
    }
    while (p1 != nullptr) {
        p1 = p1->next;
        p2 = p2->next;
    }
    p2->next = p2->next->next;
    return container->next;
}

int RemoveNthNode() {
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(2);
    l1->next->next = new ListNode(4);
    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);
    vector<ListNode*> ln = {l1, l2};
    ListNode* l3 = removeNthFromEnd(l1, 3);
    while (l3 != nullptr) {
        cout << l3->val << endl;
        l3 = l3->next;
    }
    return 0;
}