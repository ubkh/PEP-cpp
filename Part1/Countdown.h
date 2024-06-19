#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <string>
using std::string;

#include <sstream>

#include <vector>
using std::vector;


// this is provided code for the last part of the README

std::string intToString(const int x) {
    std::ostringstream str;
    str << x;
    return str.str();
}

class CountdownSolution {
  
private:
    std::string solution;
    int value;
    
public:
    
    CountdownSolution() : solution(), value(0) {}
    
    CountdownSolution(const std::string & solutionIn, const int valueIn)
        : solution(solutionIn), value(valueIn) {
    }
    
    const std::string & getSolution() const {
        return solution;
    }
    
    int getValue() const {
        return value;
    }
    
};

// Do not edit above this line

// TODO: write code here:
double evaluateCountdown(string rpn) {
    vector<double> stack;
    vector<string> tokens;
    double a, b, result =0;

    while (rpn.size() > 1) {
        int position = rpn.find(" ");
        tokens.push_back(rpn.substr(0, position));
        rpn.erase(0, position+1);
    }
    tokens.push_back(rpn);

    for (int i=0; i<tokens.size(); i++) {
        if (tokens[i]!="+" && tokens[i]!="-" && tokens[i]!="*" && tokens[i]!="/") {
            stack.push_back(std::stod(tokens[i]));
        } else if (stack.size()>0) {
            a = stack.back();
            stack.pop_back();
            b = stack.back();
            stack.pop_back();
            char c = tokens[i][0];
            switch (c) {
            case '+': result=b+a; break;
            case '-': result=b-a; break;
            case '*': result=b*a; break;
            case '/': result=b/a; break;
            }
            stack.push_back(result);
        }
    }
    return stack.size()>0 ? stack.back() : 0;
}


void permutateHelper(vector<string> s, int i, int n, vector<vector<string>> & res) {
    if (i==n-1) {
        res.push_back(s);
        return;
    }

    for (int j = i; j < n; j++) {
        std::swap(s[i], s[j]);
        permutateHelper(s, i+1, n, res);
        std::swap(s[i], s[j]);
    }
}

vector<vector<string>> permutate(vector<string> s, int i, int n) {
    vector<vector<string>> result;
    permutateHelper(s, i, n, result);
    return result;
}

void permutateWithRepetitionHelper(vector<string> s, vector<string> p, int i, int n, vector<vector<string>> & res) {
    if (i==n) {
        res.push_back(p);
        return;
    }
    for (int j=0; j<n; j++) {
        p[i] = s[j];
        permutateWithRepetitionHelper(s, p, i+1, n, res);
    }
}

vector<vector<string>> permutateWithRepetition(vector<string> s, int i, int n) {
    vector<vector<string>> result;
    vector<string> p(s.size());
    permutateWithRepetitionHelper(s, p, i, n, result);
    return result;
}

void permutateWithDistinctionHelper(vector<string> s,  int i, vector<vector<string>> & res) {
    if (i==s.size()-1) {
        res.push_back(s);
        return;
    }

    string prev = "*";

    for (int j=i; j<s.size(); j++) {
        vector<string> temp = s;
        if (j>i && temp[i]==temp[j]) continue;
        if (prev!="*" && prev==s[j]) continue;

        std::swap(temp[i], temp[j]);
        prev = s[j];

        permutateWithDistinctionHelper(temp, i+1, res);
    }
}

vector<vector<string>> permutateWithDistinction(vector<string> s, int i) {
    vector<vector<string>> result;
    permutateWithDistinctionHelper(s, i, result);
    return result;
}

// Blueprints reduce performance hit by removing all 
// invalid permutations from future calculations
bool validBlueprint(vector<string> blueprint) {
    int numCount = 0;
    for (int i=0; i<blueprint.size(); i++) {
        if (blueprint[i]=="O") {
            if (numCount<=1) return false;
            numCount--;
        } else if (blueprint[i]=="N") {
            numCount++;
        }
    }
    return true;
}

CountdownSolution solveCountdownProblem(std::vector<int> numbers, const int target) {
    vector<string> blueprint = {"N", "N", "N", "N", "N", "N", "O", "O", "O", "O", "O"};
    vector<string> validBlueprints;
    vector<string> operators = {"+", "-", "*", "/"};
    vector<string> nums;
    string rpn, bp = "";
    int result = 0;
    
    for (int n : numbers) {
        nums.push_back(intToString(n));
    }

    vector<vector<string>> bluePerms = permutateWithDistinction(blueprint, 0);

    for (vector<string> bprint : bluePerms) {
        for (string str : bprint) {
            bp.append(str);
        }
        bp.pop_back();

        if (validBlueprint(bprint)) {
            validBlueprints.push_back(bp);
        } 
        bp.clear();
    }
    
    vector<vector<string>> opPerms = permutateWithRepetition(operators, 0, operators.size());
    vector<vector<string>> numPerms = permutate(nums, 0, nums.size());
    
    int numIndex, opIndex = 0;
    int count = 0;

    for (int i=0; i<validBlueprints.size(); i++) {
        string blue = validBlueprints[i];
        vector<string> ans(blue.length());

        for (vector<string> num: numPerms) {
            for (vector<string> ops: opPerms) {
                count = 0;
                opIndex = 0;
                numIndex = 0;
                while (count < blue.length()) {
                    if (blue[count]=='O' && opIndex!=ops.size()) {
                        ans[count] = ops[opIndex];
                        opIndex++;
                    }
                    if (blue[count]=='N' && numIndex!=num.size()) {
                        ans[count] = num[numIndex];
                        numIndex++;
                    }
                    count++;
                }
                for (string str : ans) {
                    if (str!="" && str!=" ") rpn.append(str + " "); // check just in case
                }
                rpn.pop_back(); // remove final ' '

                result = evaluateCountdown(rpn);

                if (result==target) {
                    return CountdownSolution(rpn, result);
                }

                rpn.clear();
            }
        }
    }
    return CountdownSolution();
}

// Do not edit below this line


#endif
