#include "../utils/constructing.h"
#include "../utils/printing.h"
#include <iostream>

using namespace std;

namespace Solution
{
    struct ListNode 
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

    ListNode* swapPairs(ListNode* head) 
    {
        /* ... pre -> l -> r -> post */

        /* ... pre -> r -> l -> post */

        ListNode dummy(-1);
        dummy.next = head;
        auto pre = &dummy;
        auto l = head;
        auto r = nullptr != l ? l->next : nullptr;
        auto post = nullptr != r ? r->next : nullptr;

        while (nullptr != r)
        {
            pre->next = r;
            r->next = l;
            l->next = post;

            if (nullptr == post || nullptr == post->next) break;

            swap(l, r);

            pre = pre->next->next;
            r = r->next->next;
            l = l->next->next;
            post = post->next->next;
        }

        return dummy.next;
    }
}

int main()
{
    Solution::ListNode* head = nullptr;
    vector<int> data;

    data = { 1, 2, 3, 4, 5 };
    head = linked_list_from_vector<Solution::ListNode>(data);
    print_linked_list(cout, Solution::swapPairs(head));

    return 0;
}

