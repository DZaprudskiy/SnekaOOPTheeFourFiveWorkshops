/*/////////////////////////////////////////////////////////////////////////
                        Workshop 4
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

#include "CheeseShop.h"
#include <algorithm>

namespace sdds {

    // Default constructor
    CheeseShop::CheeseShop(const std::string& name) : m_name(name), m_cheeses(nullptr), m_count(0) {}

    // Destructor
    CheeseShop::~CheeseShop() {
        for (size_t i = 0; i < m_count; ++i) {
            delete m_cheeses[i];
        }
        delete[] m_cheeses; 
    }


    // Copy constructor
    CheeseShop::CheeseShop(const CheeseShop& src) : m_name(src.m_name), m_count(src.m_count) {
        m_cheeses = new const Cheese * [m_count];
        for (size_t i = 0; i < m_count; ++i) {
            m_cheeses[i] = src.m_cheeses[i];
        }
    }

    // Copy assignment operator
    CheeseShop& CheeseShop::operator=(const CheeseShop& src) {
        if (this != &src) {
            delete[] m_cheeses;
            m_name = src.m_name;
            m_count = src.m_count;
            m_cheeses = new const Cheese * [m_count];
            for (size_t i = 0; i < m_count; ++i) {
                m_cheeses[i] = src.m_cheeses[i];
            }
        }
        return *this;
    }

    // Move constructor
    CheeseShop::CheeseShop(CheeseShop&& src) noexcept : m_name(std::move(src.m_name)), m_cheeses(src.m_cheeses), m_count(src.m_count) {
        src.m_count = 0;
        src.m_cheeses = nullptr;
    }

    // Move assignment operator
    CheeseShop& CheeseShop::operator=(CheeseShop&& src) noexcept {
        if (this != &src) {
            delete[] m_cheeses;
            m_name = std::move(src.m_name);
            m_count = src.m_count;
            m_cheeses = src.m_cheeses;
            src.m_count = 0;
            src.m_cheeses = nullptr;
        }
        return *this;
    }

   

    // Add cheese to the shop
    CheeseShop& CheeseShop::addCheese(const Cheese& cheese) {
        const Cheese** temp = new const Cheese * [m_count + 1];
        for (size_t i = 0; i < m_count; ++i) {
            temp[i] = m_cheeses[i];
        }
        temp[m_count] = new Cheese(cheese); 
        
        delete[] m_cheeses; 
        
        m_cheeses = temp;
        ++m_count;
        return *this;
    }

    // Remove cheeses with 0 weight from the shop
    CheeseShop& CheeseShop::removeCheese() {
        auto newEnd = std::remove_if(m_cheeses, m_cheeses + m_count, [](const Cheese* c) {
            return c->getWeight() == 0;
            });
        size_t newSize = std::distance(m_cheeses, newEnd);

        
        for (size_t i = newSize; i < m_count; ++i) {
            delete m_cheeses[i];
        }

        const Cheese** temp = new const Cheese * [newSize];
        std::copy(m_cheeses, newEnd, temp);
        delete[] m_cheeses;
        m_cheeses = temp;
        m_count = newSize;
        return *this;
    }


    // Overloaded insertion operator to print CheeseShop details
    std::ostream& operator<<(std::ostream& os, const CheeseShop& shop) {
        os << "--------------------------\n";
        os << shop.m_name << "\n";
        os << "--------------------------\n";
        if (shop.m_count == 0) {
            os << "This shop is out of cheese!\n";
        }
        else {
            for (size_t i = 0; i < shop.m_count; ++i) {
                os << *shop.m_cheeses[i];
            }
        }
        os << "--------------------------\n";
        return os;
    }
}
