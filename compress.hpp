#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace itertools
{
// compress class
    template <typename T1, typename T2>
    class compress
    {
    //compress fields
    private:
        T1 m_container;
        T2 m_bool_container;

    public:

// iterator class
        class iterator
        {
        public:
            //iterator constructors
            iterator(typename T1::iterator from, typename T1::iterator to, typename T2::iterator bool_itr) : m_begin(from),
                                                                                                             m_end(to),
                                                                                                             m_bool_itr(bool_itr),
                                                                                                             m_current_true(*from)
            {
                while (m_begin != m_end)
                {
                    bool check = (*m_bool_itr == true);
                    if (check)
                    {
                        m_current_true = *m_begin;
                        break;
                    }
                    ++m_begin;
                    ++m_bool_itr;
                }
            }

            iterator(const iterator &other) : m_begin(other.m_begin),
                                              m_end(other.m_end),
                                              m_bool_itr(other.m_bool_itr),
                                              m_current_true(other.m_current_true) {}

            // iterator operators
            decltype(*(m_container.begin())) operator*() const
            {
                return m_current_true;
            }

            iterator &operator++()
            { //Assumes containers input is correct
                ++m_begin;
                ++m_bool_itr;
                while (m_begin != m_end)
                {
                    bool check = (*m_bool_itr == true);
                    if (check)
                    {
                        m_current_true = *m_begin;
                        break;
                    }
                    ++m_begin;
                    ++m_bool_itr;
                }
                return *this;
            }

            bool operator!=(const iterator &other) const
            {
                return m_begin != other.m_begin;
            }
        //iterator fields
        private:
            typename T1::iterator m_begin;
            typename T1::iterator m_end;
            typename T2::iterator m_bool_itr; //bool cintainer iterator
            decltype(*(m_container.begin())) m_current_true;
        };

    public:
        // compress constructors
        compress(T1 container, T2 bool_container) : m_container(container),
                                                    m_bool_container(bool_container) {}
        //compress methods
        iterator begin()
        {
            return iterator{m_container.begin(), m_container.end(), m_bool_container.begin()};
        }
        iterator end()
        {
            return iterator{m_container.end(), m_container.end(), m_bool_container.end()};
        }
    };
} // namespace itertools