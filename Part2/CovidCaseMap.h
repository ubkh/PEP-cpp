#ifndef COVIDCASEMAP_H
#define COVIDCASEMAP_H

#include "CovidCase.h"

// TODO: your code goes here
class TimeAndCaseData {
private:
    int time;
    int numCases;
    vector<CovidCase> cases;

public:
    TimeAndCaseData(int timeIn, int numCasesIn, vector<CovidCase> casesIn)
        : time(timeIn), numCases(numCasesIn), cases(casesIn) {
    }

    int getTime() {
        return time;
    }

    int getNumberOfCases() {
        return numCases;
    }

    vector<CovidCase> getCases() {
        return cases;
    }
};

class CovidCaseMap {
private:
    vector<CovidCase> cases;

public:
    void addCase(CovidCase cov) {
        cases.push_back(cov);
    }
    
    vector<TimeAndCaseData> getCasesOverTime(int hoursActive) {
        int t = 0;
        int numCases = 0;
        int prevCases = -1;
        vector<TimeAndCaseData> casesOverTime;
        vector<CovidCase> casesAtTime;

        while (t!=cases[cases.size()-1].getTime()+hoursActive+1) {
            for (int i=0; i<cases.size(); i++) {
                if (cases[i].getTime() <= t && t < cases[i].getTime()+hoursActive) {
                    numCases++;
                    casesAtTime.push_back(cases[i]);
                }   
            }
            if (numCases!=prevCases) casesOverTime.push_back(TimeAndCaseData(t, numCases, casesAtTime));
            prevCases = numCases;
            numCases=0;
            casesAtTime.clear();
            t++;
        }
       return casesOverTime;
    }

    vector<CovidCase> getActiveCases(int time, int isolationPeriod) {
        vector<CovidCase> activeCases;
        vector<TimeAndCaseData> casesOverTime = getCasesOverTime(isolationPeriod);

        for (int d=0; d<casesOverTime.size(); d++) {
            if (time == casesOverTime[d].getTime()) { activeCases = casesOverTime[d].getCases(); break; }
            if (time<casesOverTime[d].getTime()) { activeCases = casesOverTime[d-1].getCases(); break; }
        }

        return activeCases;
    }

    double supportVisitGreedyTSP(double lat, double lon, int time, int isolationPeriod) {
        struct Location
        {
            double lat;
            double lon;
        };
        Location currentLoc;
        currentLoc.lat = lat;
        currentLoc.lon = lon;
        Location startLoc = currentLoc;

        vector<CovidCase> activeCases = getActiveCases(time, isolationPeriod);
        vector<CovidCase> sorted;
        vector<CovidCase> visited;
        double shortestDistance = -1;
        double totalDistance = 0;

        while (visited.size() != activeCases.size()) {
            for (int i=0; i<activeCases.size(); i++) {
                // if visited already, don't check
                if (std::find(visited.begin(), visited.end(), activeCases[i]) == visited.end()) {
                    // is this the nearest patient?
                    double distance = activeCases[i].distanceTo(CovidCase(currentLoc.lat, currentLoc.lon, "current", 0, 0));
                    if (distance < shortestDistance || shortestDistance==-1) {
                        shortestDistance = distance;
                        sorted.push_back(activeCases[i]);
                    }
                }
            }

            currentLoc.lat = sorted.back().getLatitude();
            currentLoc.lon = sorted.back().getLongitude();
            totalDistance += shortestDistance;
            shortestDistance = -1;
            visited.push_back(sorted.back());
        }
        
        // add final step to start again
        totalDistance += visited.back().distanceTo(CovidCase(startLoc.lat, startLoc.lon, "start", 0, 0));

        return totalDistance;
    }
};

// don't write any code below this line

#endif

