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

#include "Book.h"

namespace sdds {
    Book::Book() : m_title(""), m_numChapters(1), m_numPages(10000) {}

    Book::Book(const std::string& title, unsigned nChapters, unsigned nPages)
        : m_title(title), m_numChapters(nChapters), m_numPages(nPages) {}

    std::ostream& Book::print(std::ostream& os) const {
        
        if (isValid()) 
        {
            if (m_numChapters < 10)
                os << std::setw(50) << m_title << "," << m_numChapters << "," << m_numPages
                << " | (" << std::fixed << std::setprecision(6) << static_cast<double>(m_numPages) / m_numChapters << ")    ";
            else
                os << std::setw(49) << m_title << "," << m_numChapters << "," << m_numPages
                << " | (" << std::fixed << std::setprecision(6) << static_cast<double>(m_numPages) / m_numChapters << ")    ";
        }
        else {
            os << "| Invalid book data";
        }
        return os;

    }

    std::ostream& operator<<(std::ostream& os, const Book& bk) {
        return bk.print(os);
    }

    bool Book::isValid() const {
        return !m_title.empty() && m_numChapters > 0 && m_numPages > 0;
    }

    bool Book::operator<(const Book& other) const {
        return m_numPages < other.m_numPages;
    }

    bool Book::operator>(const Book& other) const {
        return m_numPages > other.m_numPages;
    }
}
