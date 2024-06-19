#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include "Searchable.h"

#include <queue>

#include <memory>
using std::unique_ptr;
using std::priority_queue;

class Comparator {
public:
    bool operator()(unique_ptr<Searchable> & p, unique_ptr<Searchable> & q) {
        return (p->heuristicValue() > q->heuristicValue());
    }
};

class BestFirstSearch {

protected:


    /// Make sure you increment this every time you 'expand' a node, by getting it successors and putting them on the queue        
    int nodes = 0;
    priority_queue<unique_ptr<Searchable>, vector<unique_ptr<Searchable>>, Comparator> Q;

    
public:

    BestFirstSearch(std::unique_ptr<Searchable> && startFrom) {
        // TODO Put startFrom onto the queue:
        Q.push(std::move(startFrom));
    }
    
    int getNodesExpanded() const {
        return nodes;
    }
    
    Searchable * solve() {
            
        // TODO Implement search, returning a pointer to the solution (if one is found)
        // This code is mostly based on code already given in BreadthFirstSearch.h,
        // with minor modifications.
        while (!Q.empty()) {
            if (Q.top()->isSolution()) {
                return Q.top().get();
            }

            ++nodes;

            vector<unique_ptr<Searchable>> successors = Q.top()->successors();

            Q.pop();

            for (auto & s : successors) {
                Q.push(std::move(s));
            }
        }
        return nullptr;
    }
};


// Do not edit below this line

#endif
