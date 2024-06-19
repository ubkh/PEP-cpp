#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <string>
using std::string;


// TODO: your code goes here:
#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>

#include <cmath>

string longestCommonString(string a, string b) {
    string result = "";
    int shortestLength = a.length() <= b.length() ? a.length() : b.length();
    
    for (int i=0; i<shortestLength; i++) {
        if (a[i]==b[i]) {
            result += a[i];
        }
    }
    return result;
}

string longestRepeatedString(string s) {
    string result = "";
    vector<string> substrings(s.length());

    for (int i=0; i<s.length(); i++) {
        substrings[i] = s.substr(i);
    }

    std::sort(substrings.begin(), substrings.end());


    for (int i=0; i<s.length()-1; i++) {
        if (substrings[i].length() <= floor(s.length()/2)) {
            string common = longestCommonString(substrings[i], substrings[i+1]);
            if (common.length() > result.length()) {
                result = common;
            }
        }
    }

    return result;
}

int stringConstruction(string target, int cloneCost, int appendCost) {
    vector<int> cost(target.length());
    string temp;
    string lrs = longestRepeatedString(target);

    std::fill(cost.begin(), cost.end(), INT32_MAX);

    // first operation
    temp = target[0];
    cost[0] = appendCost;

    for (int i=1; i<target.length(); i++) {
        temp += target[i];
        
        if (cost[i]>cost[i-1]+1) { 
            cost[i] = cost[i-1] + appendCost;
        }


        if (temp==lrs) {
            cost[i*2+1] = cost[i]+1 > cost[i*2+1] ? cost[i*2+1] : cost[i] + cloneCost;
           
            // reset
            lrs = longestRepeatedString(temp);
            temp = "";
        }
    }
    return cost.back();
}

// do not write or edit anything below this line

#endif
