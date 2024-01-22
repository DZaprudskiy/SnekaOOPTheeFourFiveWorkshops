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


#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

#include <iostream>
#include <string>

namespace sdds {

    class Cheese {
        std::string m_name;
        size_t m_weight;
        double m_price;
        std::string m_features;

    public:
        Cheese();  // default constructor
        Cheese(const std::string& str);  // constructor with string parameter
        Cheese slice(size_t weight);  // slice cheese
        std::string getName() const;  // get cheese name
        double getPrice() const;  // get cheese price
        std::string getFeatures() const;  // get cheese features
        friend std::ostream& operator<<(std::ostream& os, const Cheese& cheese);  // insertion operator overload
    };
}

#endif
