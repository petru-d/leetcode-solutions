#include "../utils/constructing.h"
#include "../utils/printing.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

namespace Solution
{
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode dummy_head(-1);
        ListNode* tail = &dummy_head;

        int carry = 0;
        bool havel1 = nullptr != l1;
        bool havel2 = nullptr != l2;
        while ((havel1 && havel2) || 1 == carry)
        {
            auto l1_val = havel1 ? l1->val : 0;
            auto l2_val = havel2 ? l2->val : 0;
            auto sum = div(l1_val + l2_val + carry, 10);
            auto sum_node = new ListNode(sum.rem);
            carry = sum.quot;
            tail->next = sum_node;
            tail = sum_node;
            if (havel1)
            {
                l1 = l1->next;
                havel1 = nullptr != l1;
            }
            if (havel2)
            {
                l2 = l2->next;
                havel2 = nullptr != l2;
            }
        }

        if (havel1) tail->next = l1;
        if (havel2) tail->next = l2;

        return dummy_head.next;
    }
}

int main()
{
    Solution::ListNode* l1;
    Solution::ListNode* l2;

    for (int i = 0; i < 1000; ++i)
    {
        l1 = linked_list_from_vector<Solution::ListNode, int>({ 9, 8 });
        l2 = linked_list_from_vector<Solution::ListNode, int>({ 1 });
        print_linked_list(cout, Solution::addTwoNumbers(l1, l2)); cout << "\n";

        l1 = linked_list_from_vector<Solution::ListNode, int>({ 2, 4, 3 });
        l2 = linked_list_from_vector<Solution::ListNode, int>({ 5, 6, 4 });
        print_linked_list(cout, Solution::addTwoNumbers(l1, l2)); cout << "\n";

        l1 = linked_list_from_vector<Solution::ListNode, int>({ 1, 8 });
        l2 = linked_list_from_vector<Solution::ListNode, int>({ 0 });
        print_linked_list(cout, Solution::addTwoNumbers(l1, l2)); cout << "\n";
    }

    return 0;
}

