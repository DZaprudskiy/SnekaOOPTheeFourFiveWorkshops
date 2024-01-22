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

#include "CheeseParty.h"
#include <algorithm>

namespace sdds {

    // Default constructor
    CheeseParty::CheeseParty() : m_cheeses(nullptr), m_count(0) {}

    // Destructor
    CheeseParty::~CheeseParty() {
        delete[] m_cheeses;
    }

    // Copy constructor
    CheeseParty::CheeseParty(const CheeseParty& src) : m_count(src.m_count) {
        m_cheeses = new const Cheese * [m_count];
        for (size_t i = 0; i < m_count; ++i) {
            m_cheeses[i] = src.m_cheeses[i];
        }
    }

    // Copy assignment operator
    CheeseParty& CheeseParty::operator=(const CheeseParty& src) {
        if (this != &src) {
            delete[] m_cheeses;
            m_count = src.m_count;
            m_cheeses = new const Cheese * [m_count];
            for (size_t i = 0; i < m_count; ++i) {
                m_cheeses[i] = src.m_cheeses[i];
            }
        }
        return *this;
    }

    // Move constructor
    CheeseParty::CheeseParty(CheeseParty&& src) noexcept : m_cheeses(src.m_cheeses), m_count(src.m_count) {
        src.m_count = 0;
        src.m_cheeses = nullptr;
    }


    // Move assignment operator
    CheeseParty& CheeseParty::operator=(CheeseParty&& src) noexcept {
        if (this != &src) {
            delete[] m_cheeses;
            m_count = src.m_count;
            m_cheeses = src.m_cheeses;
            src.m_count = 0;
            src.m_cheeses = nullptr;
        }
        return *this;
    }



    // Add cheese to the party
    CheeseParty& CheeseParty::addCheese(const Cheese& cheese) {
        // Check if the cheese is already in the party
        auto it = std::find_if(m_cheeses, m_cheeses + m_count, [&cheese](const Cheese* c) {
            return c == &cheese;
            });

       
        if (it == m_cheeses + m_count) {
            const Cheese** temp = new const Cheese * [m_count + 1];
            for (size_t i = 0; i < m_count; ++i) {
                temp[i] = m_cheeses[i];
            }
            temp[m_count] = &cheese;
            delete[] m_cheeses;
            m_cheeses = temp;
            ++m_count;
        }
        return *this;
    }


    // Remove cheeses with 0 weight from the party
    CheeseParty& CheeseParty::removeCheese() {
        auto newEnd = std::remove_if(m_cheeses, m_cheeses + m_count, [](const Cheese* c) {
            return c->getWeight() == 0;
            });
        size_t newSize = std::distance(m_cheeses, newEnd);
        const Cheese** temp = new const Cheese * [newSize];
        std::copy(m_cheeses, newEnd, temp);
        delete[] m_cheeses;
        m_cheeses = temp;
        m_count = newSize;
        return *this;
    }


    // Overloaded insertion operator to print CheeseParty details
    std::ostream& operator<<(std::ostream& os, const CheeseParty& party) {
        os << "--------------------------\n";
        os << "Cheese Party\n";
        os << "--------------------------\n";
        if (party.m_count == 0) {
            os << "This party is just getting started!\n";
        }
        else {
            for (size_t i = 0; i < party.m_count; ++i) {
                os << *party.m_cheeses[i];
            }
        }
        os << "--------------------------\n";
        return os;
    }
}
