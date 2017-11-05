#include <vector>
#include <iostream>

#include "../utils/constructing.h"
#include "../utils/printing.h"

using namespace std;

namespace Solution
{
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        auto curr = head;

        for (int i = 0; i < n - 1; ++i) curr = curr->next;

        auto nth = head;
        ListNode* pre_nth = nullptr;

        while (curr->next != nullptr)
        {
            pre_nth = nth;
            nth = nth->next;

            curr = curr->next;
        }

        if (nullptr == pre_nth)
        {
            auto new_head = head->next;
            delete head;
            return new_head;
        }
        else
        {
            pre_nth->next = nth->next;
            delete nth;
            return head;
        }
    };
}

int main()
{
    vector<int> v;

    v = { 1, 2, 3, 4, 5 };
    auto h = Solution::removeNthFromEnd(linked_list_from_vector<Solution::ListNode>(v), 2);

    print_linked_list(cout, h);

    return 0;
}

