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

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>
#include <string>
#include <iomanip>

namespace sdds {
    class Book {
        std::string m_title{};
        unsigned m_numChapters{};
        unsigned m_numPages{};
    public:
        Book();
        Book(const std::string& title, unsigned nChapters, unsigned nPages);

        std::ostream& print(std::ostream& os) const;
        friend std::ostream& operator<<(std::ostream& os, const Book& bk);
        bool isValid() const;

        bool operator<(const Book& other) const;
        bool operator>(const Book& other) const;
    };
}

#endif // SDDS_BOOK_H
