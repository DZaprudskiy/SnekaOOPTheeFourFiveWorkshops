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

#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H

#include <iostream>
#include <string>
#include "Cheese.h"

namespace sdds {

    class CheeseShop {
        std::string m_name;
        const Cheese** m_cheeses;  // Array of pointers to Cheese objects
        size_t m_count;  // Number of cheeses in the shop

    public:
        CheeseShop(const std::string& name = "No Name");
        ~CheeseShop();
        CheeseShop(const CheeseShop& src);
        CheeseShop& operator=(const CheeseShop& src);
        CheeseShop(CheeseShop&& src) noexcept;
        CheeseShop& operator=(CheeseShop&& src) noexcept;

        CheeseShop& addCheese(const Cheese& cheese);
        CheeseShop& removeCheese();

        friend std::ostream& operator<<(std::ostream& os, const CheeseShop& shop);
    };
}

#endif
