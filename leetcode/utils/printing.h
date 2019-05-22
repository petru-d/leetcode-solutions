#pragma once
#include <vector>
#include <string>
#include <bitset>
#include <iostream>
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

inline void print_vector(std::ostream& of, const std::vector<std::string>& v)
{
    of << "[";
    if (!v.empty())
    {
        of << "\n\t\"" << v[0] <<"\"";
        for (auto i = 1; i < v.size(); ++i)
        {
            of << ",\n\t\"" << v[i] << "\"";
        }
    }
    of << "\n]";
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

template<int N, int B>
void print_array(std::ostream& of, std::bitset<B> data[N])
{
    of << "[";
    if (N != 0)
    {
        of << data[0];
        for (auto i = 1; i < N; ++i)
        {
            of << ", " << data[i].to_string();
        }
    }
    of << "]";
}

template<typename T, int N>
void print_array(std::ostream& of, T data[N])
{
    of << "[";
    if (N != 0)
    {
        of << data[0];
        for (auto i = 1; i < N; ++i)
        {
            of << ", " << data[i];
        }
    }
    of << "]";
}

template<typename T, int L, int C>
void print_array_array(std::ostream& of, T data[L][C])
{
    of << "[";
    if (0 != L)
    {
        of << "\n\t";
        print_array<T, C>(of, data[0]);

        for (auto i = 1; i < L; ++i)
        {
            of << ",\n\t";
            print_array<T, C>(of, data[i]);
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
