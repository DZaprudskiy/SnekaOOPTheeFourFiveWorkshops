/*/////////////////////////////////////////////////////////////////////////
                        Final Project - Milestone 3
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


#include "LineManager.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

namespace sdds {

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) : m_cntCustomerOrder(0), m_firstStation(nullptr) {
    std::ifstream ifs(file);
    if (!ifs) {
        throw std::string("Unable to open [") + file + "] file.";
    }

    
    std::string record;
    while (std::getline(ifs, record)) {
        auto delimiterPos = record.find('|');
        std::string firstStationName = record.substr(0, delimiterPos);
        auto it = std::find_if(stations.begin(), stations.end(), [firstStationName](const Workstation* station) {
            return station->getItemName() == firstStationName;
        });

        if (it != stations.end()) {
            m_activeLine.push_back(*it);
        }
    }

    ifs.clear();
    ifs.seekg(0);
    while (std::getline(ifs, record)) {
        auto delimiterPos = record.find('|');
        if (delimiterPos != std::string::npos) {
            
            std::string firstStationName = record.substr(0, delimiterPos);
            std::string secondStationName = record.substr(delimiterPos + 1);

            auto first = std::find_if(m_activeLine.begin(), m_activeLine.end(), [firstStationName](const Workstation* station) {
                return station->getItemName() == firstStationName;
                });

            auto second = std::find_if(m_activeLine.begin(), m_activeLine.end(), [secondStationName](const Workstation* station) {
                return station->getItemName() == secondStationName;
                });

            if (first != m_activeLine.end() && second != m_activeLine.end()) {
                (*first)->setNextStation(*second);
            }
        }
        else {

            std::string firstStationName = record;
            auto first = std::find_if(m_activeLine.begin(), m_activeLine.end(), [firstStationName](const Workstation* station) {
                return station->getItemName() == firstStationName;
                });

            if (first != m_activeLine.end()) {
                (*first)->setNextStation(nullptr);
            }
        }
    }

    
    auto it = std::find_if(m_activeLine.begin(), m_activeLine.end(), [](const Workstation* station) {
        return station->getNextStation() == nullptr;
    });

    if (it != m_activeLine.end()) {
        m_firstStation = *it;
    }

    m_cntCustomerOrder = g_pending.size();
}




    void LineManager::reorderStations() {
        auto findStation = [this](const std::string& itemName) {
            return std::find_if(m_activeLine.begin(), m_activeLine.end(), [itemName](const Workstation* station) {
                return station->getItemName() == itemName;
                });
        };

        auto isFirstStation = [this](const Workstation* station) {
            return std::none_of(m_activeLine.begin(), m_activeLine.end(), [station](const Workstation* otherStation) {
                return otherStation->getNextStation() == station;
                });
        };

        auto firstStation = std::find_if(m_activeLine.begin(), m_activeLine.end(), isFirstStation);

        if (firstStation == m_activeLine.end()) {
            throw std::runtime_error("Error: Unable to determine the first station for reordering.");
        }

        std::vector<Workstation*> dummy;
        dummy.push_back(*firstStation);

        for (size_t i = 0; i < m_activeLine.size() - 1; ++i) {
            auto currentStation = findStation(dummy.back()->getNextStation()->getItemName());

            if (currentStation != m_activeLine.end()) {
                dummy.push_back(*currentStation);
            }
            else {
                throw std::runtime_error("Error: Unable to find subsequent station for reordering.");
            }
        }

        m_activeLine = dummy;
        m_firstStation = m_activeLine.front();


    }




    bool LineManager::run(std::ostream& os) {
        static size_t iterationCount = 0;
        bool allOrdersProcessed = false;
        iterationCount++;

        os << "Line Manager Iteration: " << iterationCount << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (const auto &item : m_activeLine) {
            item->fill(os);
        }

        for (auto& item : m_activeLine) {
            item->attemptToMoveOrder();
        }

        if (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder) {
            allOrdersProcessed = true;
        }

        return allOrdersProcessed;
    }






    void LineManager::display(std::ostream& os) const {
        for (const auto& station : m_activeLine) {
            station->display(os);
        }
    }
}
