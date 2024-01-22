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

#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <string>
#include <list>
#include "Covid.h"

namespace sdds {

    class CovidCollection {
        std::list<Covid> m_covidData;

    public:
        CovidCollection(const char* filename);
        void display(std::ostream& out) const;
    };

    std::ostream& operator<<(std::ostream& out, const Covid& theCovid);

}

#endif // SDDS_COVIDCOLLECTION_H
