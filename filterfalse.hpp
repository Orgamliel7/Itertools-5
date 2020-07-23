#pragma once

namespace itertools
{
  /*
  מקבל כקלט שני פרמטרים: הראשון - פונקטור בוליאני המייצג תנאי, והשני הוא מיכל או דמוי-מיכל 
 מחזיר דמוי-מיכל חדש, הכולל רק את האיברים בדמוי-המיכל הנתון, שאינם מקיימים את התנאי
  דוגמא:  filterfalse([](int i){return i%2==0;}, range(5,9))
  האיברים בטווח ש*לא מקיימים* את התנאי הם 5,7 בלבד
  */

    template <typename F, typename C>
    class filterfalse
    {
    protected:
        C container;
        F filter;

    public:
        filterfalse(F f, C c)
            : filter(f), container(c) {}

        class iterator
        {
        protected:
            F filter;
            typename C::iterator it;
            typename C::iterator last;

        public:
            iterator(F fil, typename C::iterator first, typename C::iterator l)
                : filter(fil), it(first), last(l) {
                    while (it != last && filter(*it))
                    ++it;
                }

            // ++i העמסת אופרטור
            iterator &operator++()
            {
                ++it;
                while (it != last && filter(*it))
                    ++it;
                return *this;
            }
            // i++; העמסת אופרטור
            iterator operator++(int)
            {
                iterator i = *this;
                ++(*this);
                return i;
            }
            bool operator==(const iterator &other) const // העמסת אופרטור לבדיקת שיוויון
            {
                return it == other.it;
            }
            bool operator!=(const iterator &other) const // העמסת אופרטור לבדיקת אי שיוויון
            {
                return it != other.it;
            }
            auto operator*() // העמסת אופרטור די רפרנס
            {
                return *it;
            }

            iterator &operator=(const iterator &other)
            {
                if (*this != other)
                {
                    this->it = other.it;
                    this->last = other.last;
                    this->filter = other.filter;
                }
                return *this;
            }
        };
        iterator begin()
        {
            return iterator(filter, container.begin(), container.end());
        }

        iterator end()
        {
            return iterator(filter, container.end(), container.end());
        }
    };
}
