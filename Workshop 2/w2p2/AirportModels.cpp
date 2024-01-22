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
#include "Timer.h"

namespace sdds {

    Airport::Airport()
        : code(""), name(""), city(""), state(""), country(""), latitude(0.0), longitude(0.0) {

    }

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

    std::ostream& operator<<(std::ostream& os, const Airport& airport) {
        if (airport.code.empty()) {
            os << "Empty Airport";
        }
        else {
            os << std::setw(23) << std::setfill('.') << std::right << "Airport Code : " << std::left << std::setw(30) << std::setfill('.') << airport.code << '\n'
                << std::setw(23) << std::setfill('.') << std::right << "Airport Name : " << std::left << std::setw(30) << std::setfill('.') << airport.name << '\n'
                << std::setw(23) << std::setfill('.') << std::right << "City : " << std::left << std::setw(30) << std::setfill('.') << airport.city << '\n'
                << std::setw(23) << std::setfill('.') << std::right << "State : " << std::left << std::setw(30) << std::setfill('.') << airport.state << '\n'
                << std::setw(23) << std::setfill('.') << std::right << "Country : " << std::left << std::setw(30) << std::setfill('.') << airport.country << '\n'
                << std::setw(23) << std::setfill('.') << std::right << "Latitude : " << std::left << std::setw(30) << std::setfill('.') << airport.latitude << '\n'
                << std::setw(23) << std::setfill('.') << std::right << "Longitude : " << std::left << std::setw(30) << std::setfill('.') << airport.longitude << '\n';
        }
        return os;
    }

    AirportLog::AirportLog()
        : airports(nullptr), numAirports(0) {}

    AirportLog::AirportLog(const char* filename)
        : airports(nullptr), numAirports(0) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }

        std::string header;
        std::getline(file, header);

        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
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
                        Airport* newAirports = new Airport[numAirports + 1];

                        for (size_t i = 0; i < numAirports; i++) {
                            newAirports[i] = airports[i];
                        }

                        newAirports[numAirports] = Airport(code, name, city, state, country, latitude, longitude);

        
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

    AirportLog::~AirportLog() {
        delete[] airports;
    }

    AirportLog::AirportLog(AirportLog&& other)
        : airports(other.airports), numAirports(other.numAirports) {
        other.airports = nullptr;
        other.numAirports = 0;
    }

    AirportLog& AirportLog::operator=(AirportLog&& other) {
        if (this != &other) {
            delete[] airports;
            airports = other.airports;
            numAirports = other.numAirports;
            other.airports = nullptr;
            other.numAirports = 0;
        }
        return *this;
    }

    AirportLog::AirportLog(const AirportLog& other)
        : airports(new Airport[other.numAirports]), numAirports(other.numAirports) {
        for (size_t i = 0; i < numAirports; ++i) {
            airports[i] = other.airports[i];
        }
    }

    AirportLog& AirportLog::operator=(const AirportLog& other) {
        if (this != &other) {
            Airport* newAirports = new Airport[other.numAirports];
            for (size_t i = 0; i < other.numAirports; ++i) {
                newAirports[i] = other.airports[i];
            }
            delete[] airports;
            airports = newAirports;
            numAirports = other.numAirports;
        }
        return *this;
    }

    void AirportLog::addAirport(const Airport& airport) {
        Airport* newAirports = new Airport[numAirports + 1];
        for (size_t i = 0; i < numAirports; i++) {
            newAirports[i] = airports[i];
        }
        newAirports[numAirports] = airport;
        numAirports++;
        delete[] airports;
        airports = newAirports;
    }

    AirportLog AirportLog::findAirport(const char* state, const char* country) const {
        AirportLog foundAirports;
        for (size_t i = 0; i < numAirports; i++) {
            if (airports[i].state == state && airports[i].country == country) {
                foundAirports.addAirport(airports[i]);
            }
        }
        return foundAirports;
    }

    const Airport& AirportLog::operator[](size_t index) const {
        if (index < numAirports) {
            return airports[index];
        }
        else {
            
            static Airport emptyAirport;
            return emptyAirport;
        }
    }



    AirportLog::operator size_t() const {
        return numAirports;
    }

}  // namespace sdds
