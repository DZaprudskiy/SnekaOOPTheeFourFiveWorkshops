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

#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H

#include "Cheese.h"

namespace sdds {

    class CheeseParty {
        const Cheese** m_cheeses;  // Array of pointers to Cheese objects
        size_t m_count;  // Number of cheeses in the party

    public:
        CheeseParty();
        ~CheeseParty();
        CheeseParty(const CheeseParty& src);
        CheeseParty& operator=(const CheeseParty& src);
        CheeseParty(CheeseParty&& src) noexcept;
        CheeseParty& operator=(CheeseParty&& src) noexcept;

        CheeseParty& addCheese(const Cheese& cheese);
        CheeseParty& removeCheese();

        friend std::ostream& operator<<(std::ostream& os, const CheeseParty& party);
    };
}

#endif
