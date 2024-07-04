// * Q: https://leetcode.cn/problems/partition-list/

#include <iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
ListNode* partition(ListNode* head, int x) {
    ListNode *small = new ListNode(), *big = new ListNode();
    ListNode *p1 = small, *p2 = big;
    ListNode* temp;
    while (head != nullptr) {
        if (head->val < x) {
            p1->next = head;
            p1 = p1->next;
        } else {
            p2->next = head;
            p2 = p2->next;
        }
        temp = head->next;
        head->next = nullptr;
        head = temp;
    }
    // 头尾相接
    p1->next = big->next;
    return small->next;
}
int PartitionList() {
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(3);
    l1->next->next->next = new ListNode(2);
    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);
    ListNode* l3 = partition(l1, 3);
    while (l3 != nullptr) {
        cout << l3->val << endl;
        l3 = l3->next;
    }
    return 0;
}