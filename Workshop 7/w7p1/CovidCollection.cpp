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

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "CovidCollection.h"

namespace sdds {

    CovidCollection::CovidCollection(const char* filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::invalid_argument("Invalid filename");
        }

        std::string line;
        while (std::getline(file, line)) {
            std::string country = line.substr(0, 25);
            std::string city = line.substr(25, 25);
            std::string variant = line.substr(50, 25);
            int year = std::stoi(line.substr(75, 5));
            unsigned int cases = std::stoi(line.substr(80, 5));
            unsigned int deaths = std::stoi(line.substr(85, 5));

            // Remove leading and trailing spaces from strings
            country = country.substr(country.find_first_not_of(' '), country.find_last_not_of(' ') + 1);
            city = city.substr(city.find_first_not_of(' '), city.find_last_not_of(' ') + 1);
            variant = variant.substr(variant.find_first_not_of(' '), variant.find_last_not_of(' ') + 1);

            m_covidData.push_back({ country, city, variant, year, cases, deaths });
        }
    }

    void CovidCollection::display(std::ostream& out) const {
        std::for_each(m_covidData.begin(), m_covidData.end(),
            [&out](const Covid& c) {
                out << "| " << std::setw(21) << std::left << c.country << " | "
                    << std::setw(15) << std::left << c.city << " | "
                    << std::setw(20) << std::left << c.variant << " | ";
                if (c.year >= 0) {
                    out << std::setw(6) << std::right << c.year;
                }
                else {
                    out << std::setw(6) << std::right << "";
                }
                out << " | "
                    << std::setw(4) << std::right << c.cases << " | "
                    << std::setw(3) << std::right << c.deaths << " |\n";
                
            }
        );
    }


    std::ostream& operator<<(std::ostream& out, const Covid& theCovid) {
        out << "| " << std::setw(21) << std::left << theCovid.country << " | "
            << std::setw(15) << std::left << theCovid.city << " | "
            << std::setw(20) << std::left << theCovid.variant << " | "
            << std::setw(6) << std::right << theCovid.year << " | "
            << std::setw(4) << std::right << theCovid.cases << " | "
            << std::setw(3) << std::right << theCovid.deaths << " |";

        return out;
    }

}
