#include "../utils/printing.h"
#include "../utils/constructing.h"

#include <iostream>

using namespace std;

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

namespace Solution
{
	ListNode* reverse(ListNode* from, ListNode* to)
	{
		auto from_next(from->next);
		from->next = nullptr;
		while (to != from_next)
		{
			auto from_next_next(from_next->next);
			from_next->next = from;
			from = from_next;
			from_next = from_next_next;
		}
		to->next = from;

		return to;
	}

	ListNode* reverseKGroup2(ListNode* head, int k)
	{
		if (1 >= k) return head;

		// Add a fake head to make further processing easier
		ListNode fake_head(-1); fake_head.next = head;
		auto before_sequence = &fake_head;

		while (true)
		{
			if (nullptr == before_sequence->next) break;

			auto start_sequence = before_sequence->next;

			auto end_sequence(before_sequence);
			for (int i = 0; i < k; ++i)
			{
				end_sequence = end_sequence->next;
				if (nullptr == end_sequence) return fake_head.next;
			}

			auto last_sequence = nullptr == end_sequence->next;
			ListNode* pre_fake_tail(start_sequence);
			if (last_sequence)
			{
				ListNode fake_tail(-1); fake_tail.next = nullptr;
				end_sequence->next = &fake_tail;
			}

			auto after_sequence = end_sequence->next;

			reverse(start_sequence, end_sequence);

			before_sequence->next = end_sequence;

			start_sequence->next = after_sequence;

			if (last_sequence)
			{
				pre_fake_tail->next = nullptr;
				break;
			}

			before_sequence = start_sequence;
		}

		return fake_head.next;
	}

	ListNode *reverseKGroup(ListNode *head, int k) 
	{
		if (head == nullptr || k == 1) return head;

		int num = 0;
		ListNode *preheader = new ListNode(-1); preheader->next = head;


		// one traversal to find out how many elements there are
		auto n(preheader);
		while (nullptr != (n = n->next))
			++num;

		auto pre(preheader); 
		while (num >= k)
		{
			//Do k swaps - this will reverse the current group.
			auto cur = pre->next;
			auto nex = cur->next;
			for (int i = 1; i < k; ++i) 
			{
				cur->next = nex->next;
				nex->next = pre->next;
				pre->next = nex;
				nex = cur->next;
			}

			//Prepare the next iteration.
			pre = cur;
			num -= k;
		}
		return preheader->next;
	}
}

int main()
{

	auto head = linked_list_from_vector<ListNode, int>({ 1, 2, 3, 4, 5, 6, 7, 8 });

	print_linked_list(cout, Solution::reverseKGroup(head, 2));

	head = linked_list_from_vector<ListNode, int>({ 1 });
	print_linked_list(cout, Solution::reverseKGroup(head, 2));

	return 0;
}

