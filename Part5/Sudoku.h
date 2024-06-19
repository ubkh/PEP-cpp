#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"

// TODO: Your Sudoku class goes here:
#include "SudokuSquare.h"

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

#include <cmath>

#include <tuple>
using std::pair;

class Sudoku : public Searchable {
private:
    int size;
    int boxSize;
    vector<vector<SudokuSquareSet>> incompleteSolution;
    struct Box {
        int colStart;
        int colEnd;
        int rowStart;
        int rowEnd;
    };
    vector<Box> boxes;

public:
    Sudoku(const int sizeIn)
        : size(sizeIn) {
        
        SudokuSquareSet cell;
        for (int i=1; i<size+1; i++) cell.insert(i);
        
        for (int x=0; x<size; x++) {
            vector<SudokuSquareSet> thisVec;
            for (int y=0; y<size; y++) {
                SudokuSquareSet thisSet = cell;
                thisVec.push_back(thisSet);
            }
            incompleteSolution.push_back(thisVec);
        }
        boxSize = sqrt(size);

        for (int r=0; r<size; r+=boxSize) {
            for (int c=0; c<size; c+=boxSize) {
                Box box;
                box.colStart = c;
                box.colEnd = c + boxSize-1;
                box.rowStart = r;
                box.rowEnd = r + boxSize-1;
                boxes.push_back(box);
            }
        }
    }

    int getSquare(int row, int col) const {
        return incompleteSolution[row][col].size()>1 ? -1 : *incompleteSolution[row][col].begin();
    }

    bool setSquare(int row, int col, int value) {
        bool change = true, empty = false;
        incompleteSolution[row][col].clear();
        incompleteSolution[row][col].insert(value);

        while (change) {
            change = false;
            for (int a=0; a<size; a++) {
                for (int b=0; b<size; b++) {
                    if (incompleteSolution[a][b].size()==1) {
                        empty = removeValFromRow(a, b, *incompleteSolution[a][b].begin(), change);
                        if (empty) return false;
                        empty = removeValFromCol(a, b, *incompleteSolution[a][b].begin(), change);
                        if (empty) return false;
                        empty = removeValFromBox(a, b, *incompleteSolution[a][b].begin(), change);
                        if (empty) return false;
                    }
                }
            }
        }
        return true;
    }

    bool removeValFromRow(int & row, int & avoidCol, int value, bool & change) {
        for (int i=0; i<size; i++) {
            if (i==avoidCol) continue;
            int setSize = incompleteSolution[row][i].size();
            incompleteSolution[row][i].erase(value);
            if (incompleteSolution[row][i].size()!=setSize) change = true;
            if (incompleteSolution[row][i].empty()) return true;
        }
        return false;
    }

    bool removeValFromCol(int & avoidRow, int & col, int value, bool & change) {
        for (int i=0; i<size; i++) {
            if (i==avoidRow) continue;
            int setSize = incompleteSolution[i][col].size();
            incompleteSolution[i][col].erase(value);
            if (incompleteSolution[i][col].size()!=setSize) change = true;
            if (incompleteSolution[i][col].empty()) return true;
        }
        return false;
    }

    bool removeValFromBox(int & row, int & col, int value, bool & change) {
        Box box;
        // find box
        for (Box b : boxes) {
            if (col >= b.colStart && col <= b.colEnd
                && row >= b.rowStart && row <= b.rowEnd) {
                box = b;
                break;
            }
        }

        for (int r=box.rowStart; r<box.rowEnd+1; r++) {
            for (int c=box.colStart; c<box.colEnd+1; c++) {
                if (r==row && c==col) continue;
                int setSize = incompleteSolution[r][c].size();
                incompleteSolution[r][c].erase(value);
                if (incompleteSolution[r][c].size()!=setSize) change = true;
                if (incompleteSolution[r][c].empty()) return true;
            }
        }

        return false;
    }

    virtual bool isSolution() const override {
        for (vector<SudokuSquareSet> v : incompleteSolution) {
            for (SudokuSquareSet s : v) {
                if (s.size()!=1) return false;
            }
        }
        return true;
    }

    virtual void write(ostream & o) const override {
        for (vector<SudokuSquareSet> v : incompleteSolution) {
            for (SudokuSquareSet s : v) {
                if (s.size()>1) cout << " ";
                else if (s.empty()) cout << "E";
                else cout << *s.begin();
            }
            cout << endl;
        }
    }

    virtual vector<unique_ptr<Searchable>> successors() const override {
        vector<unique_ptr<Searchable>> s;

        for (int x=0; x<size; x++) {
            for (int y=0; y<size; y++) {
                if (incompleteSolution[x][y].size()>1) {
                    SudokuSquareSet leftmost = incompleteSolution[x][y];
                    for (int option : leftmost) {
                        Sudoku* copy = new Sudoku(*this);
                        if (copy->setSquare(x,y,option)==true) {
                            s.push_back(unique_ptr<Searchable>(copy));
                        } else { delete copy; }
                    }
                    if (s.size()==1 && !s.at(0)->isSolution()){
                        return s.at(0)->successors();
                    }
                    return s;
                }
            }
        }
        return s;
    }

    virtual int heuristicValue() const override {
        int count = 0;
        for (vector<SudokuSquareSet> v : incompleteSolution) {
            for (SudokuSquareSet s : v) {
                if (s.size()!=1) count++;
            }
        }
        return count;
    }
};



#endif
