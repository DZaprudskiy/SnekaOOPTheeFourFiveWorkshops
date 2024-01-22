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
#include <iterator>
#include <numeric> 
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

            Covid newCovid;
            newCovid.country = country;
            newCovid.city = city;
            newCovid.variant = variant;
            newCovid.year = year;
            newCovid.cases = cases;
            newCovid.deaths = deaths;

            m_covidData.push_back(newCovid);

        }

        // Calculate world total cases and deaths
        m_worldTotalCases = std::accumulate(m_covidData.begin(), m_covidData.end(), 0.0,
            [](double total, const Covid& c) { return total + c.cases; });

        m_worldTotalDeaths = std::accumulate(m_covidData.begin(), m_covidData.end(), 0.0,
            [](double total, const Covid& c) { return total + c.deaths; });
    }


    void CovidCollection::display(std::ostream& out, const std::string& country) const {
        if (country != "ALL") {
            out << "Displaying information of country = " << country << "\n";

            double totalCountryCases = 0.0;
            double totalCountryDeaths = 0.0;
            double totalGlobalCases = m_worldTotalCases;
            double totalGlobalDeaths = m_worldTotalDeaths;

            std::for_each(m_covidData.begin(), m_covidData.end(),
                [&out, &country, &totalCountryCases, &totalCountryDeaths](const Covid& c) {
                    if (c.country == country) {
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
                            << std::setw(3) << std::right << c.deaths << " |"
                            << " | " << std::setw(8) << std::right << c.status << " |\n";

                        totalCountryCases += c.cases;
                        totalCountryDeaths += c.deaths;
                    }
                }
            );


            double percentageGlobalCases = (totalCountryCases / totalGlobalCases) * 100;
            double percentageGlobalDeaths = (totalCountryDeaths / totalGlobalDeaths) * 100;

            int intTotalCountryCases = static_cast<int>(totalCountryCases);
            int intTotalCountryDeaths = static_cast<int>(totalCountryDeaths);


            out << "----------------------------------------------------------------------------------------\n";
            out << "|" << std::setw(79 - country.length()) <<"Total cases in " << country << ": " << std::setw(4) << intTotalCountryCases << " |\n";
            out << "|"<< std::setw(79 - country.length()) << "Total deaths in " << country << ": " << std::setw(4) << intTotalCountryDeaths << " |\n";
            out << "|";


            std::string phrase = country + " has " + std::to_string(percentageGlobalCases) + "% of global cases and " + std::to_string(percentageGlobalDeaths) + "% of global deaths";
   
            out << std::setw(85) << std::right << phrase << " |\n";


        }
        else {
            //out << "Displaying information for all countries\n";

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
                << std::setw(3) << std::right << c.deaths << " |"
                << " | " << std::setw(8) << std::right << c.status << " |\n";
                }
            );
            
            // Calculate world total cases and deaths
            double totalCases = std::accumulate(m_covidData.begin(), m_covidData.end(), 0.0,
                [](double total, const Covid& c) { return total + c.cases; });

            double totalDeaths = std::accumulate(m_covidData.begin(), m_covidData.end(), 0.0,
                [](double total, const Covid& c) { return total + c.deaths; });

            int intTotalCases = static_cast<int>(totalCases);
            int intTotalDeaths = static_cast<int>(totalDeaths);


            out << "|                                                  Total cases around the world: " << std::setw(5) << intTotalCases << " |\n";
            out << "|                                                 Total deaths around the world: " << std::setw(5) << intTotalDeaths << " |\n";
        }

        
    }


    


    std::ostream& operator<<(std::ostream& out, const Covid& theCovid) {
        out << "| " << std::setw(21) << std::left << theCovid.country << " | "
            << std::setw(15) << std::left << theCovid.city << " | "
            << std::setw(20) << std::left << theCovid.variant << " | "
            << std::setw(6) << std::right << theCovid.year << " | "
            << std::setw(4) << std::right << theCovid.cases << " | "
            << std::setw(3) << std::right << theCovid.deaths << " | | "
            << std::setw(8) << std::right << theCovid.status << " |";

        return out;
    }


    void CovidCollection::sort(const std::string& field) {
        if (field == "DEFAULT") {
            m_covidData.sort([](const Covid& a, const Covid& b) {
                return a.deaths < b.deaths || (a.deaths == b.deaths && a.variant < b.variant);
                });
        }
        else if (field == "country") {
            m_covidData.sort([](const Covid& a, const Covid& b) {
                return a.country < b.country || (a.country == b.country && a.deaths < b.deaths);
                });
        }
        else if (field == "year") {
            m_covidData.sort([](const Covid& a, const Covid& b) {
                return a.year < b.year || (a.year == b.year && a.deaths < b.deaths);
                });
        }
        else if (field == "variant") {
            m_covidData.sort([](const Covid& a, const Covid& b) {
                return a.variant < b.variant || (a.variant == b.variant && a.deaths < b.deaths);
                });
        }
    }


    bool CovidCollection::inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const {
        return std::any_of(m_covidData.begin(), m_covidData.end(), [&](const Covid& c) {
            return c.variant == variant && c.country == country && c.deaths > deaths;
            });
    }

    std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const {
        std::list<Covid> result;
        std::copy_if(m_covidData.begin(), m_covidData.end(), std::back_inserter(result),
            [deaths](const Covid& c) { return c.deaths >= deaths; });
        return result;
    }

    void CovidCollection::updateStatus() {
        std::for_each(m_covidData.begin(), m_covidData.end(), [](Covid& c) {
            if (c.deaths > 300) {
                c.status = "EPIDEMIC";
            }
            else if (c.deaths < 50) {
                c.status = "EARLY";
            }
            else {
                c.status = "MILD";
            }
            });
    }

}
