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
    
     ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
     {
         ListNode dummy(0);
         ListNode* tail = &dummy;

         while (nullptr != l1 && nullptr != l2)
         {
             if (l1->val < l2->val)
             {
                 tail->next = l1;
                 tail = l1;
                 l1 = l1->next;
             }
             else
             {
                 tail->next = l2;
                 tail = l2;
                 l2 = l2->next;
             }
         }

         if (l1 != nullptr)
         {
             tail->next = l1;
         }
         if (l2 != nullptr)
         {
             tail->next = l2;
         }

         return dummy.next;
     }
}

int main()
{
    auto l1 = linked_list_from_vector<Solution::ListNode, int>({ 1, 3, 5, 7 });
    auto l2 = linked_list_from_vector<Solution::ListNode, int>({ 2, 4, 6, 8 });

    auto l = Solution::mergeTwoLists(l1, l2);

    print_linked_list(cout, l);

    return 0;
}

