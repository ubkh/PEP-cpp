// TODO: Replace this file with your CovidCase.h from Part1
// then extend as per the instructions in README.md

#ifndef COVIDCASE_H
#define COVIDCASE_H

#include <iostream>
using std::ostream;

// TODO: your code  goes here
#include <string>
using std::string;

#include <cmath>

#include <vector>
using std::vector;

#include <algorithm>

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

    CovidCase(string input) {
        vector<string> params;
        int position = 0;
        
        while (position!=-1) {
            position = input.find(", ");
            params.push_back(input.substr(0, position));
            input.erase(0, position+2);
        }
        params.push_back(input.erase(0));

        params[2].erase(remove(params[2].begin(), params[2].end(), '"'), params[2].end());

        latitude = std::stod(params[0]);
        longitude = std::stod(params[1]);
        name = params[2];
        age = std::stoi(params[3]);
        positiveSince = std::stoi(params[4]);
        // CovidCase(std::stod(params[0]), std::stod(params[1]), 
        // params[2], std::stoi(params[3]), std::stoi(params[4]));
    }

    double getLatitude() {
        return latitude;
    }

    double getLongitude() {
        return longitude;
    }

    string getName() {
        return name;
    }

    int getAge() {
        return age;
    }

    int getTime() {
        return positiveSince;
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

    bool operator==(const CovidCase other) {
        return (latitude==other.latitude &&
                longitude==other.longitude &&
                name==other.name &&
                age==other.age &&
                positiveSince==other.positiveSince);
    }
};

ostream & operator<<(ostream & o, const CovidCase & rhs) {
    rhs.write(o);
    return o;
}

// don't write any code below this line

#endif


