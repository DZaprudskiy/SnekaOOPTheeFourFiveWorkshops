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

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>
#include <string>

namespace sdds {
    class Book {
        std::string m_author;
        std::string m_title;
        std::string m_country;
        size_t m_year;
        double m_price;
        std::string m_description;

    public:
        Book(); // Default constructor
        Book(const std::string& strBook); // Constructor taking a string

        const std::string& title() const;
        const std::string& country() const;
        const size_t& year() const;
        double& price();

        friend std::ostream& operator<<(std::ostream& os, const Book& book);
    };
}

#endif // SDDS_BOOK_H
