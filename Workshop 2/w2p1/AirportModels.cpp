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


#include <iomanip>
#include <sstream> 
#include "AirportModels.h"

namespace sdds {

    Airport::Airport()
        : code(""), name(""), city(""), state(""), country(""), latitude(0.0), longitude(0.0) {
        
    }

    // Airport constructor
    Airport::Airport(
        const std::string& code,
        const std::string& name,
        const std::string& city,
        const std::string& state,
        const std::string& country,
        double latitude,
        double longitude
    ) {
        // Initialize the attributes with the provided values
        this->code = code;
        this->name = name;
        this->city = city;
        this->state = state;
        this->country = country;
        this->latitude = latitude;
        this->longitude = longitude;
    }

    // Overload the insertion operator to output an Airport object
    std::ostream& operator<<(std::ostream& os, const Airport& airport) {
        if (airport.code.empty()) {
            os << "Empty Airport";
        }
        else {
            os  << std::setw(23) << std::setfill('.') << std::right << "Airport Code : " << std::left << std::setw(30) << std::setfill('.') << airport.code << '\n'
                << std::setw(23) << std::setfill('.') << std::right << "Airport Name : " << std::left << std::setw(30) << std::setfill('.') << airport.name << '\n'
                << std::setw(23) << std::setfill('.') << std::right << "City : " << std::left << std::setw(30) << std::setfill('.') << airport.city << '\n'
                << std::setw(23) << std::setfill('.') << std::right << "State : " << std::left << std::setw(30) << std::setfill('.') << airport.state << '\n'
                << std::setw(23) << std::setfill('.') << std::right << "Country : " << std::left << std::setw(30) << std::setfill('.') << airport.country << '\n'
                << std::setw(23) << std::setfill('.') << std::right << "Latitude : " << std::left << std::setw(30) << std::setfill('.') << airport.latitude << '\n'
                << std::setw(23) << std::setfill('.') << std::right << "Longitude : " << std::left << std::setw(30) << std::setfill('.') << airport.longitude << '\n';
        }
        return os;
    }

    // AirportLog default constructor
    AirportLog::AirportLog() : airports(nullptr), numAirports(0) {}

    // AirportLog one-argument constructor
    AirportLog::AirportLog(const char* filename) : airports(nullptr), numAirports(0) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }

        
        // Read and ignore the header line if it exists
        std::string header;
        std::getline(file, header);

        // Read airport data from the file
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                // Parse and store airport data using ',' as the delimiter
                std::istringstream iss(line);
                std::string code, name, city, state, country;
                double latitude, longitude;
                if (std::getline(iss, code, ',') &&
                    std::getline(iss, name, ',') &&
                    std::getline(iss, city, ',') &&
                    std::getline(iss, state, ',') &&
                    std::getline(iss, country, ',') &&
                    (iss >> latitude) && (iss.ignore(), iss >> longitude)) {

                    if (numAirports < SIZE_MAX) {
                        // Create a new array with one more element
                        Airport* newAirports = new Airport[numAirports + 1];

                        // Copy existing airports to the new array
                        for (size_t i = 0; i < numAirports; i++) {
                            newAirports[i] = airports[i];
                        }

                        // Add the new airport to the end
                        newAirports[numAirports] = Airport(code, name, city, state, country, latitude, longitude);

                        // Update the count and pointer
                        numAirports++;
                        delete[] airports;
                        airports = newAirports;
                    }
                }
                else {
                    std::cerr << "Error: Failed to parse airport data in line: " << line << std::endl;
                }
            }
        }

        file.close();
    }


    // AirportLog destructor
    AirportLog::~AirportLog() {
        delete[] airports;
    }

    // Add an Airport object to the dynamic array
    void AirportLog::addAirport(const Airport& airport) {
        // Create a new array with one more element
        Airport* newAirports = new Airport[numAirports + 1];

        // Copy existing airports to the new array
        for (size_t i = 0; i < numAirports; i++) {
            newAirports[i] = airports[i];
        }

        // Add the new airport to the end
        newAirports[numAirports] = airport;

        // Update the count and pointer
        numAirports++;
        delete[] airports;
        airports = newAirports;
    }

    // Find airports in a specific state and country
    AirportLog AirportLog::findAirport(const char* state, const char* country) const {
        AirportLog foundAirports;
        for (size_t i = 0; i < numAirports; i++) {
            if (airports[i].state == state && airports[i].country == country) {
                foundAirports.addAirport(airports[i]);
            }
        }
        return foundAirports;
    }

    // Overload the subscript operator to access airports by index
    const Airport& AirportLog::operator[](size_t index) const {
        if (index >= numAirports) {
            static Airport emptyAirport;
            return emptyAirport;
        }
        return airports[index];
    }

    // Overload the size_t casting operator to get the number of airports
    AirportLog::operator size_t() const {
        return numAirports;
    }

}  // namespace sdds
