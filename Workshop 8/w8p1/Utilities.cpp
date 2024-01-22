/*/////////////////////////////////////////////////////////////////////////
                        Workshop 8
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

// Workshop 8 - Smart Pointers
// 2019/11 - Cornel

#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {

    bool areProfilesEqual(const Profile& profile1, const Profile& profile2) {
        return profile1.m_name.first_name == profile2.m_name.first_name &&
            profile1.m_name.last_name == profile2.m_name.last_name &&
            profile1.m_age == profile2.m_age;
    }

	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		// TODO: Add your code here to build a collection of Profiles.
		//         The result should contain only profiles from `allProfiles`
		//         which are not in `bannedProfiles` using Raw Pointers.


        for (size_t i = 0; i < allProfiles.size(); ++i) {
            const Profile& currentProfile = allProfiles[i];
            bool isBanned = false;

            for (size_t j = 0; j < bannedProfiles.size(); ++j) {
                
                if (areProfilesEqual(currentProfile, bannedProfiles[j])) {
                    isBanned = true;
                    break;
                }
            }

            if (!isBanned) {
                try {
                    Profile* validatedProfile = new Profile(currentProfile.m_name, currentProfile.m_address, currentProfile.m_age);
                    if (validatedProfile->validateAddress()) {
                        result += validatedProfile;
                    }
                    else {
                        delete validatedProfile;
                        throw std::string("*** Invalid Address ***");
                    }
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                    
                }
            }
        }





		return result;
	}
}
