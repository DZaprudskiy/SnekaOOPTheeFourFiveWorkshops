/*/////////////////////////////////////////////////////////////////////////
                        Workshop 3
Full Name  :    David Zaprudskiy
Student ID#:    147850226
Email      :    dzaprudskiy@myseneca.ca
Section    :    NRA
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include "Book.h"
#include <iostream>
#include <limits>

namespace sdds {
    template <typename T, unsigned C>
    class Collection {
        T m_items[C]{};
        unsigned m_size{ 0 };
        static T m_smallestItem;
        static T m_largestItem;
        
        void setSmallestItem(const T& item) {
            if (m_size == 0 || item < m_smallestItem) {
                m_smallestItem = item;
            }
        }

        void setLargestItem(const T& item) {
            if (m_size == 0 || item > m_largestItem) {
                m_largestItem = item;
            }
        }

    public:
        Collection() {
            m_smallestItem = std::numeric_limits<T>::max();
        }
        
        unsigned size() const {
            return m_size;
        }

        unsigned capacity() const {
            return C;
        }

        bool operator+=(const T& item) {
            if (m_size < C) {
                m_items[m_size] = item;
                m_size++;
                setSmallestItem(item);
                setLargestItem(item);
                return true;
            }
            return false;
        }

        std::ostream& print(std::ostream& os) const {
            os << "[";
            for (unsigned i = 0; i < m_size; ++i) {
                os << std::fixed << std::setprecision(1) << m_items[i];
                if (i < m_size - 1) 
                    os << ",";
            }
            os << "]" << std::endl;
            return os;
        }

        static T getSmallestItem() {
            return m_smallestItem;
        }

        static T getLargestItem() {
            return m_largestItem;
        }
    };

    template <typename T, unsigned C>
    T Collection<T, C>::m_smallestItem{};

    template <typename T, unsigned C>
    T Collection<T, C>::m_largestItem{};
}

#endif // SDDS_COLLECTION_H
