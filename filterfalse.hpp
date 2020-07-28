#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace itertools
{

    template <typename F, typename T>
    class filterfalse
    {
    private:
        T m_container;
        F m_function;

    public:
        // iterator class
        class iterator
        {
        public:
            //iterator constructors
            iterator(typename T::iterator from, typename T::iterator to, F func) : m_begin(from),
                                                                                   m_end(to),
                                                                                   m_ifunction(func),
                                                                                   m_current_false(*from)
            {
                while (m_begin != m_end)
                {
                    bool check = m_ifunction(*m_begin);
                    if (!check)
                    {
                        m_current_false = *m_begin;
                        break;
                    }
                    ++m_begin;
                }
                
            }

            iterator(const iterator &other) : m_begin(other.m_begin),
                                              m_end(other.m_end),
                                              m_ifunction(other.m_ifunction),
                                              m_current_false(other.m_current_false) {}

            //iterator operators
            typename T::value_type operator*() const
            {

                return m_current_false;
            }

            iterator &operator++()
            {
                ++m_begin;
                while (m_begin != m_end)
                {
                    bool check = m_ifunction(*m_begin);
                    if (!check)
                    {
                        m_current_false = *m_begin;
                        break;
                    }
                    ++m_begin;
                }
                return *this;
            }


            bool operator!=(const iterator &other) const
            {
                return m_begin != other.m_begin;
            }
        //iterator fields
        private:
            typename T::iterator m_begin;
            typename T::iterator m_end;
            F m_ifunction;
            typename T::value_type m_current_false;
        };

    public:
        // filterfalse constructor
        filterfalse(F func, T container) : m_container(container),
                                           m_function(func) {}
        // filterfalse methods
        iterator begin()
        {
            return iterator{m_container.begin(), m_container.end(), m_function};
        }
        iterator end()
        {
            return iterator{m_container.end(), m_container.end(), m_function};
        }
    };
} // namespace itertools