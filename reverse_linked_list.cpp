#include<vector>

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {};
    ListNode(int x) : val(x), next(nullptr) {};
    ListNode(int x, ListNode* next) : val(x), next(next) {};    
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        return reverseListRecursive(head);
    }

    ListNode* reverseListIterative(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while(curr != nullptr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    };

    ListNode* reverseListRecursive(ListNode* head) {
        return reverseListRecursiveUtil(head, nullptr);
    }

    ListNode* reverseListRecursiveUtil(ListNode* curr, ListNode* prev) {
        if(curr == nullptr)
            return prev;
        
        ListNode* forward = curr->next;
        curr->next = prev;

        return reverseListRecursiveUtil(curr, forward);
    }
};