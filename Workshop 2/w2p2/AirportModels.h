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
        std::string code;       
        std::string name;       
        std::string city;       
        std::string state;      
        std::string country;    
        double latitude;        
        double longitude;       

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

        friend std::ostream& operator<<(std::ostream& os, const Airport& airport);
    };

    class AirportLog {
    private:
        Airport* airports;        // Dynamic array of Airport objects
        size_t numAirports;       // Number of airports in the array

    public:
        AirportLog();

        AirportLog(const char* filename);

        ~AirportLog();

        AirportLog(AirportLog&& other);

        AirportLog& operator=(AirportLog&& other);

        AirportLog(const AirportLog& other);

        AirportLog& operator=(const AirportLog& other);

        void addAirport(const Airport& airport);

        AirportLog findAirport(const char* state, const char* country) const;

        const Airport& operator[](size_t index) const;

        operator size_t() const;
    };

}  // namespace sdds

#endif // SDDS_AIRPORTMODELS_H
