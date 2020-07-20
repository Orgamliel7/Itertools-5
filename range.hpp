#pragma once
#include <iostream>

namespace itertools
{
class range 
{
public:
    int start_ind, end_ind;

public:
    range(int from, int to) : start_ind(from), end_ind(to) {}; // בנאי השמה עם רשימת אתחול 

    class iterator
    {
    public: // דיפולטיבית זה גישה פרטית
        iterator(int curr = 0) : curr(curr) {}; 
    private:
        int curr;

        iterator operator++() // ++i
        {
            curr = curr + 1;
            return *this; // return curr - equivalent?
        };

        iterator operator++(int) // i++
        {
            iterator temp = curr;
            curr = curr + 1;
            return temp;
        };

        bool operator!=(iterator &other) const { return curr != other.curr; };

        bool operator==(const iterator &it) const { return curr == it.curr; };

        int operator*() { return curr; };


        iterator begin() { return iterator(start_ind); };

        iterator end() { return iterator(end_ind); };
    };
};


