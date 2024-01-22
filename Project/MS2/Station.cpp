/*/////////////////////////////////////////////////////////////////////////
                        Final Project - Milestone 1
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
#include <string>
#include <istream>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 0;

    Station::Station(const std::string& str) {
        Utilities util;
        bool more = true;
        size_t next_pos = 0;

        m_itemName = util.extractToken(str, next_pos, more);
        m_serialNumber = std::stoi(util.extractToken(str, next_pos, more));
        m_quantity = std::stoi(util.extractToken(str, next_pos, more));
        m_description = util.extractToken(str, next_pos, more);

        size_t startPos = m_description.find_first_not_of(" \t\n\r\f\v");
        m_description = (startPos != std::string::npos) ? m_description.substr(startPos) : "";


        if (util.getFieldWidth() > m_widthField)
            m_widthField = util.getFieldWidth();

        m_id = ++id_generator;
    }

    const std::string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {
        if (m_quantity > 0)
            m_quantity--;
    }

    void Station::display(std::ostream& os, bool full) const {
        os << std::setw(3) << std::setfill('0') << m_id
            << " | " << std::setw(m_widthField - 14) << std::left << std::setfill(' ') << m_itemName
            << "| " << std::setw(6) << std::right << std::setfill('0') << m_serialNumber << " | ";

        if (full)
        {
            os << std::setw(4) << std::right << std::setfill(' ') << m_quantity
                << " | " << m_description;
        }

        os << std::endl;
    }
}
