#pragma once
#include <functional>

using namespace std;

namespace itertools
{
    //  מקבל כקלט מיכל או דמוי-מיכל כלשהו. מחזיר דמוי-מיכל חדש הכולל סכומים חלקיים. 
    auto _sum = [](auto x, auto y) { return x + y; };

    template <typename C, typename F = decltype(_sum)> //  return type depends on template parameters 
    class accumulate
    {
    protected:
        C container;
        F function;

    public:
        accumulate(C c, F f = _sum)
            : container(c), function(f) {}

        class iterator // מחלקת איטרטור שנגדיר לה אופרטורים 
        {
        protected:
            F function;
            typename C::iterator it; // איטרטור להתחלת המיכל
            typename C::iterator last; // איטרטור לסוף המיכל
            typename decay<decltype(*(container.begin()))>::type aggr;//ערך מצטבר
            

        public:
            iterator(typename C::iterator first, typename C::iterator l, F fun) // בנאי למחלקת איטרטור המקבל שני איטרטורים ופונקטור בינארי 
                : it(first), last(l), function(fun) // רשימת אתחול 
            {
                if (it != last) 
                    aggr = *it;
            }

            // ++i;
            iterator &operator++()
            {
                ++it;
                if (it != last)
                    aggr = function(aggr, *it);
                return *this;
            }
            // i++;
            iterator operator++(int)
            {
                iterator i = *this;
                ++(*i);
                return i;
            }
            bool operator==(const iterator &other) const
            {
                return (it == other.it);
            }
            bool operator!=(const iterator &other) const
            {
                return (it != other.it);
            }
            auto operator*() const
            {
                return aggr;
            }

            iterator &operator=(const iterator &other)
            {
                if (*this != other)
                {
                    this->it = other.it;
                    this->last = other.last;
                    this->aggr = other.aggr;
                    this->function = other.function;
                }
                return *this;
            }
        };
        iterator begin()
        {
            return iterator(container.begin(), container.end(), function);
        }

        iterator end()
        {
            return iterator(container.end(), container.end(), function);
        }
    };
} 
