/*/////////////////////////////////////////////////////////////////////////
                        Final Project - Milestone 2
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
#include <algorithm>

#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds {
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder() : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {}


    CustomerOrder::CustomerOrder(const std::string& record) : CustomerOrder() {
        Utilities util;
        size_t pos = 0;
        bool more = true;

        m_name = util.extractToken(record, pos, more);
        m_product = util.extractToken(record, pos, more);

        m_name.erase(0, m_name.find_first_not_of(" \t\n\r\f\v"));
        m_name.erase(m_name.find_last_not_of(" \t\n\r\f\v") + 1);

        m_product.erase(0, m_product.find_first_not_of(" \t\n\r\f\v"));
        m_product.erase(m_product.find_last_not_of(" \t\n\r\f\v") + 1);

        m_cntItem = std::count(record.begin(), record.end(), util.getDelimiter()) - 1;

        if (m_cntItem > 0) {
            m_lstItem = new Item * [m_cntItem];
            for (size_t i = 0; i < m_cntItem; ++i) {
                m_lstItem[i] = new Item(util.extractToken(record, pos, more));

                m_lstItem[i]->m_itemName.erase(0, m_lstItem[i]->m_itemName.find_first_not_of(" \t\n\r\f\v"));
                m_lstItem[i]->m_itemName.erase(m_lstItem[i]->m_itemName.find_last_not_of(" \t\n\r\f\v") + 1);
            }

            if (util.getFieldWidth() > m_widthField) {
                m_widthField = util.getFieldWidth();
            }
        }
    }


    CustomerOrder::CustomerOrder(const CustomerOrder& src) {
        throw std::string("Copy operations are not allowed");
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
        m_name = std::move(src.m_name);
        m_product = std::move(src.m_product);
        m_cntItem = src.m_cntItem;
        m_lstItem = src.m_lstItem;

        src.m_cntItem = 0;
        src.m_lstItem = nullptr;
        src.setEmpty();
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
        if (this != &src) {
           
            setEmpty();

            m_name = std::move(src.m_name);
            m_product = std::move(src.m_product);
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;

            src.m_cntItem = 0;
            src.m_lstItem = nullptr;

            if (src.m_lstItem) {
                for (size_t i = 0; i < src.m_cntItem; ++i) {
                    delete src.m_lstItem[i];
                }

                setEmpty();
            }
        }
        return *this;
    }


    void CustomerOrder::setEmpty() {
        if (m_lstItem != nullptr) {
            for (size_t i = 0; i < m_cntItem; ++i) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
            m_lstItem = nullptr;
        }
    }

    CustomerOrder::~CustomerOrder() {
        setEmpty();
    }


    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (!m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    
                    break;
                }
                else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }



    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; ++i) {
            os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] "
                << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName
                << " - "
                << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }
}