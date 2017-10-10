#pragma once
#include <fstream>
#include <vector>

template<typename T>
void print_vector(std::ostream& of, const std::vector<T>& v)
{
    of << "[";
    if (!v.empty())
    {
        of << v[0];
        for (auto i = 1; i < v.size(); ++i)
        {
            of << ", " << v[i];
        }
    }
    of << "]";
}

template<typename T>
void print_vector_vector(std::ostream& of, const std::vector<std::vector<T>>& vv)
{
    of << "[";
    if (!vv.empty())
    {
        of << "\n\t";
        print_vector(of, vv[0]);
        for (auto i = 1; i < vv.size(); ++i)
        {
            of << ",\n\t";
            print_vector(of, vv[i]);
        }
    }
    of << "\n]";
}

template<typename T>
void print_linked_list(std::ostream& of, const T* head)
{
    of << "[";
    if (nullptr != head)
    {
        of << head->val;
        head = head->next;
        while (nullptr != head)
        {
            of << "->";
            of << head->val;
            head = head->next;
        }
    }
    of << "]";
}