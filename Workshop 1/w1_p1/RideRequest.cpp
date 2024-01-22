/*/////////////////////////////////////////////////////////////////////////
                        Workshop 1
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
#include <iomanip>
#include "RideRequest.h"

namespace sdds {

    double g_taxrate = 0.0;
    double g_discount = 0.0;

    int RideRequest::counter = 0;

    RideRequest::RideRequest() {
        m_customerName[0] = '\0';
        m_rideDescription[0] = '\0';
        m_rate = 0.0;
        m_discount = false;
    }

    void RideRequest::read(std::istream& in) {
        if (in) {
            in.getline(m_customerName, 11, ',');
            in.getline(m_rideDescription, 26, ',');
            in >> m_rate;
            char discountStatus;
            in.ignore();
            in.get(discountStatus);
            m_discount = (discountStatus == 'Y');
            in.ignore(); 
        }
    }

    void RideRequest::display() const {
        counter++;
        std::cout << std::left << std::setw(2) << counter << ". ";
        
        if (m_customerName[0] == '\0') {
            std::cout << "No Ride Request" << std::endl;
        }
        else {
            double priceWithTax = m_rate * (1 + g_taxrate);
            std::cout << std::left << std::setw(10) << m_customerName << "|";
            std::cout << std::left << std::setw(25) << m_rideDescription << "|";
            std::cout << std::fixed << std::setprecision(2);
            std::cout << std::left << std::setw(12) << priceWithTax << "|";
            if (m_discount) {
                double priceWithDiscount = priceWithTax - g_discount;
                std::cout << std::right << std::setw(13) << priceWithDiscount;
            }
            
            std::cout << std::endl;
        }
    }

}
