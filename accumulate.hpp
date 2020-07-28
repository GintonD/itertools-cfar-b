#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace itertools
{

//Default functor
    class plus
    {
    public:
        template <typename T2>
        T2 operator()(T2 a, T2 b)
        {
            return a + b;
        }
    };


//Accumulate class
    template <typename T, typename F = plus>
    class accumulate
    {
    private:
        T m_container;
        F m_function;

    public:

 // iterator class
        class iterator
        {
         //iterator constructors
        public:
            iterator(typename T::iterator from, typename T::iterator to, F func) : m_begin(from),
                                                                                   m_end(to),
                                                                                   m_ifunction(func),
                                                                                   m_current_sum(*from) { }

            iterator(typename T::iterator from, typename T::iterator to) : m_begin(from),
                                                                            m_end(to)
                                                                                    { }                                                                       
            iterator(const iterator &other) : m_begin(other.m_begin),
                                              m_end(other.m_end),
                                              m_ifunction(other.m_ifunction),
                                              m_current_sum(other.m_current_sum) {}

            //iterator operators
           typename T::value_type operator*() const
            {
                // cout << "in operator* --- " << m_current_sum << endl;
                return m_current_sum;
            }

            iterator &operator++()
            {

                ++m_begin;
                if (m_begin != m_end)
                {
                    m_current_sum = m_ifunction(m_current_sum, *m_begin);

                }
                return *this;
            }

            bool operator!=(const iterator &other) const
            {
                // cout << "in operator!= --- " <<  endl;
                return m_begin != other.m_begin;
            }
        //iterator fields
        private:
            typename T::iterator m_begin;
            typename T::iterator m_end;
            F m_ifunction;
            typename T::value_type m_current_sum;
        };


    public:
        // accumulate constructor
        accumulate(T container, F func = plus()) : m_container(container), m_function(func) {}

        // accumulate methods
        iterator begin()
        {
            return iterator{m_container.begin(), m_container.end(), m_function};
        }

        iterator end()
        {
      
            return iterator{m_container.end(), m_container.end()};
        }
    };
} // namespace itertools
