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

#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H

#include <chrono>

namespace sdds {

    class Timer {
    public:
        Timer();
        void start();
        long long stop();

    private:
        std::chrono::steady_clock::time_point m_startTime;
    };

}  // namespace sdds

#endif // SDDS_TIMER_H
