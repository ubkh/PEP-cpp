#ifndef COVIDCASE_H
#define COVIDCASE_H

#include <iostream>
using std::ostream;

// TODO: your code  goes here

#include <string>
using std::string;

#include <cmath>

class CovidCase {
private:
    double latitude;
    double longitude;
    string name;
    int age;
    int positiveSince;

public:
    CovidCase(double lat, double lon, string nameIn, int ageIn, int positive)
        : latitude(lat), longitude(lon), name(nameIn), age(ageIn), positiveSince(positive) {
        
    }

    void write(ostream & o) const {
        o << "{" << latitude
          << ", "
          << longitude
          << ", "
          << "\"" << name << "\""
          << ", "
          << age
          << ", "
          << positiveSince << "}";
    }

    double toRadians(const double degrees) {
        return degrees * (M_PI / 180);
    }

    double distanceTo(const CovidCase & caseIn) {
        const double lat1 = toRadians(latitude);
        const double lat2 = toRadians(caseIn.latitude);

        // Haversline formula
        const double dlon = toRadians(caseIn.longitude) - toRadians(longitude);
        const double dlat = lat2 - lat1;

        const double a = pow((sin(dlat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlon/2)), 2);
        const double c = 2 * atan2( sqrt(a), sqrt(1-a));
        const double distance = 3960 * c;

        return distance;
    }
};

ostream & operator<<(ostream & o, const CovidCase & rhs) {
    rhs.write(o);
    return o;
}

// don't write any code below this line

#endif

