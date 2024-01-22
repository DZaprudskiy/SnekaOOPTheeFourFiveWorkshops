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


#include "Cheese.h"
#include <sstream>
#include <iomanip>

namespace sdds {

    Cheese::Cheese() : m_name("Not a Cheese"), m_weight(0), m_price(0.0), m_features("") {}

    Cheese::Cheese(const std::string& str) {
        std::istringstream iss(str);
        std::getline(iss >> std::ws, m_name, ',');  
        std::string weightStr, priceStr, feature;
        std::getline(iss, weightStr, ',');
        std::getline(iss, priceStr, ',');
        m_weight = std::stoul(weightStr);
        m_price = std::stod(priceStr);
        while (std::getline(iss, feature, ',')) {
            feature.erase(0, feature.find_first_not_of(" \t"));  
            feature.erase(feature.find_last_not_of(" \t") + 1);  
            m_features += feature + " ";
        }
        m_features.pop_back();  
    }



    Cheese Cheese::slice(size_t weight) {
        Cheese slicedCheese(*this);
        if (weight <= m_weight) {
            slicedCheese.m_weight = weight;
            m_weight -= weight;
        }
        else {
            slicedCheese.m_name = "NaC";
            slicedCheese.m_weight = 0;
            slicedCheese.m_price = 0.0;
            slicedCheese.m_features = "";
            
        }
        return slicedCheese;
    }


    std::string Cheese::getName() const {
        return m_name;
    }

    double Cheese::getPrice() const {
        return m_price;
    }

    std::string Cheese::getFeatures() const {
        return m_features;
    }

    std::ostream& operator<<(std::ostream& os, const Cheese& cheese) {
        os  << "|" << std::setw(21) << std::left << cheese.m_name
            << "|" << std::setw(5) << cheese.m_weight
            << "|" << std::fixed << std::setprecision(2) << std::setw(5) << cheese.m_price
            << "|" << std::setw(33) << std::right << cheese.m_features
            << " |" << std::endl;
        return os;
    }
}
