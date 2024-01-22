/*/////////////////////////////////////////////////////////////////////////
                        Workshop 2
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


#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <iostream>
#include <fstream>
#include <string>

namespace sdds {

    struct Airport {
        std::string code;         // Airport code
        std::string name;         // Airport name
        std::string city;         // Airport city
        std::string state;        // Airport state
        std::string country;      // Airport country
        double latitude;          // Airport latitude
        double longitude;         // Airport longitude

        Airport();

        // Constructor
        Airport(
            const std::string& code,
            const std::string& name,
            const std::string& city,
            const std::string& state,
            const std::string& country,
            double latitude,
            double longitude
        );

        // Overload the insertion operator to output an Airport object
        friend std::ostream& operator<<(std::ostream& os, const Airport& airport);
    };

    class AirportLog {
    private:
        Airport* airports;        // Dynamic array of Airport objects
        size_t numAirports;       // Number of airports in the array

    public:
        // Default constructor
        AirportLog();

        // One argument constructor that reads data from a file
        AirportLog(const char* filename);

        // Destructor to release memory
        ~AirportLog();

        // Add an Airport object to the dynamic array
        void addAirport(const Airport& airport);

        // Find airports in a specific state and country
        AirportLog findAirport(const char* state, const char* country) const;

        // Overload the subscript operator to access airports by index
        const Airport& operator[](size_t index) const;

        // Overload the size_t casting operator to get the number of airports
        operator size_t() const;
    };

}  // namespace sdds

#endif // SDDS_AIRPORTMODELS_H
