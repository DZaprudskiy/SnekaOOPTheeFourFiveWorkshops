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

#include "Utilities.h"

namespace sdds {
    char Utilities::m_delimiter = ',';

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        size_t delimiterPos = str.find(m_delimiter, next_pos);
        std::string token;

        if (delimiterPos != std::string::npos) {
            token = str.substr(next_pos, delimiterPos - next_pos);
            next_pos = delimiterPos + 1;
            more = true;
        }
        else {
            token = str.substr(next_pos);
            next_pos = str.length();
            more = false;
        }

        if (token.empty()) {
            more = false;
            throw "ERROR: No token.";
        }

        if (token.length() > m_widthField)
            m_widthField = token.length();

        return token;
    }


    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }
}
