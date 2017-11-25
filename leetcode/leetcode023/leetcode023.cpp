#include "../utils/constructing.h"
#include "../utils/printing.h"
#include <iostream>
#include <algorithm>

using namespace std;

namespace Solution
{
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) 
    {
        lists.erase(std::remove(lists.begin(), lists.end(), nullptr), lists.end());

        ListNode dummy(-1);
        auto head = &dummy;

        auto compare = [](ListNode* l, ListNode* r)
        {
            return l->val > r->val;
        };

        std::make_heap(lists.begin(), lists.end(), compare);

        while (!lists.empty())
        {
            std::pop_heap(lists.begin(), lists.end(), compare);

            head->next = lists.back();
            head = head->next;

            if (nullptr != lists.back()->next)
            {
                lists.back() = lists.back()->next;
                std::push_heap(lists.begin(), lists.end(), compare);
            }
            else
            {
                lists.pop_back();
            }
        }

        return dummy.next;
    }
}

int main()
{
    vector<vector<int>> data;
    vector<Solution::ListNode*> lists;

    data = { {  } };
    for (const auto& d : data)
    {
        lists.push_back(linked_list_from_vector<Solution::ListNode>(d));
    }
    print_linked_list(cout, Solution::mergeKLists(lists));

    data = { { 1, 4, 7, 10, 13 },{ 2, 5, 8, 11, 14 }, { 3, 6, 9, 12, 15 } };
    for (const auto& d : data)
    {
        lists.push_back(linked_list_from_vector<Solution::ListNode>(d));
    }
    print_linked_list(cout, Solution::mergeKLists(lists));

    return 0;
}

