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
        double m_worldTotalCases;
        double m_worldTotalDeaths;

    public:
        CovidCollection(const char* filename);
        void display(std::ostream& out, const std::string& country = "ALL") const;
        void sort(const std::string& field = "country");
        bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const;
        std::list<Covid> getListForDeaths(unsigned int deaths) const;
        void updateStatus();
    };

    std::ostream& operator<<(std::ostream& out, const Covid& theCovid);

}

#endif // SDDS_COVIDCOLLECTION_H
