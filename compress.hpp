#pragma once

namespace itertools
{
    /*
מקבל כקלט שני מיכלים או דמויי-מיכלים, שחייבים להיות באותו אורך
הראשון כולל עצמים מסוג כלשהו, והשני חייב לכלול עצמים מסוג בוליאני
true מחזיר דמוי-מיכל חדש שבו מופיעים איברים מהדמוי-מיכל הראשון, שהאיבר המתאים להם בדמוי-מיכל השני הוא
*/
    template <typename C, typename B>
    class compress
    {
    protected:
        C container; // מיכל/דמוי מיכל עצמים כלשהוא
        B b_container; // מיכל/דמוי מיכל עצמים בוליאני

    public:
        compress(C c, B b)
            : container(c), b_container(b) {}

        class iterator
        {
        protected:
            typename C::iterator it; // איטרטור לתחילת המיכל הרגיל
            typename C::iterator last; // איטרטור לסוף המיכל הרגיל
            typename B::iterator b_it; //איטרטור בוליאני

        public:
            iterator(typename C::iterator first, typename C::iterator l, typename B::iterator b)
                : it(first), last(l), b_it(b)
            {
                while (it != last && !(*b_it)) //במיכל הבינארי false כל עוד לא הגענו לסוף המיכל הרגיל וגם יש 
                {
                    ++it; // קידום המיכל הרגיל
                    ++b_it; // קידום המיכל הבינארי
                }
            }

            // ++i העמסת האופרטור
            iterator &operator++()
            {
                ++it;
                ++b_it;
                while (it != last && !(*b_it))
                {
                    ++it;
                    ++b_it;
                }
                return *this;
            }
            // i++;
            iterator operator++(int)
            {
                iterator i = *this;
                ++(*this);
                return i;
            }
            bool operator==(const iterator &other) const
            {
                return it == other.it;
            }
            bool operator!=(const iterator &other) const
            {
                return it != other.it;
            }
            auto operator*()
            {
                return *it;
            }

            iterator &operator=(const iterator &other)
            {
                if (*this != other)
                {
                    this->it = other.it;
                    this->last = other.last;
                    this->b_it = other.b_it;
                }
                return *this;
            }
        };
        iterator begin()
        {
            return iterator(container.begin(), container.end(), b_container.begin());
        }

        iterator end()
        {
            return iterator(container.end(), container.end(), b_container.end());
        }
    };
}
