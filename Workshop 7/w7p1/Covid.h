/*/////////////////////////////////////////////////////////////////////////
                        Workshop 7
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

#ifndef SDDS_COVID_H
#define SDDS_COVID_H

#include <string>

namespace sdds {

    struct Covid {
        std::string country;
        std::string city;
        std::string variant;
        int year;
        unsigned int cases;
        unsigned int deaths;
    };

}

#endif // SDDS_COVID_H
