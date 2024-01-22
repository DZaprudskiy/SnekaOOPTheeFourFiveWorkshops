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


#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

namespace sdds {

    class RideRequest;

    extern double g_taxrate;
    extern double g_discount;

    void setTaxRate(double rate);
    void setDiscount(double discount);

    class RideRequest {
        char m_customerName[11];
        char m_rideDescription[26];
        double m_rate;
        bool m_discount;
        static int counter;

    public:
        RideRequest();

        void read(std::istream& in);

        void display() const;
    };
}

#endif // SDDS_RIDEREQUEST_H
