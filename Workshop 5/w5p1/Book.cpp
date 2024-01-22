/*/////////////////////////////////////////////////////////////////////////
                        Workshop 5
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
#include <sstream>
#include <iomanip>

namespace sdds {
    
    // Default constructor
    Book::Book() : m_year(0), m_price(0) {}

    // Constructor taking a string
    Book::Book(const std::string& strBook) {
        std::stringstream ss(strBook);
        ss >> std::ws;
        std::getline(ss, m_author, ',');
        m_author.erase(m_author.find_last_not_of(" \t") + 1);

        ss >> std::ws;
        std::getline(ss, m_title, ',');
        m_title.erase(m_title.find_last_not_of(" \t") + 1);

        ss >> std::ws;
        std::getline(ss, m_country, ',');
        m_country.erase(m_country.find_last_not_of(" \t") + 1);

        ss >> m_price;
        ss.ignore();
        ss >> m_year;
        ss.ignore();
        std::getline(ss >> std::ws, m_description);
    }



    const std::string& Book::title() const {
        return m_title;
    }

    const std::string& Book::country() const {
        return m_country;
    }

    const size_t& Book::year() const {
        return m_year;
    }

    double& Book::price() {
        return m_price;
    }

    // Friend function to overload the insertion operator
    std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << std::setw(20) << std::right << book.m_author << " | ";
        os << std::setw(22) << std::right << book.m_title << " | ";
        os << std::setw(5) << std::right << book.m_country << " | ";
        os << std::setw(4) << std::right << book.m_year << " | ";
        os << std::fixed << std::setprecision(2) << std::setw(6) << std::right << book.m_price << " | ";
        os << book.m_description << endl;;
        return os;
    }


}
