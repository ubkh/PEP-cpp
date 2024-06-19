#ifndef SUDOKUSQUARE_H
#define SUDOKUSQUARE_H

// Do not add any #include statements to this file
class SudokuSquareIterator {
private:
    unsigned int values;
    int current;

public:
    SudokuSquareIterator(unsigned int vals, unsigned int i) 
        : values(vals), current(i) {
    }

    int operator*() {
        return current+1;
    }

    // prefix
    void operator++() {
        unsigned int copy = values;
        bool found = false;

        copy = copy >> (current+1);

        while (!found && current<26) {
            current++;
            if ((copy & 1)!=1) {
                copy = copy >> 1;
            } else {
                found = true;
                return;
            }
        }
        current = -1;
    }
    
    bool operator==(SudokuSquareIterator other) const {
        return other.current == current
            && other.values == values;
    }

    bool operator!=(SudokuSquareIterator other) const {
        return other.current != current
            || other.values != values;
    }

    unsigned int getCurrent() {
        return current;
    }
};

class SudokuSquareSet {
private:
    unsigned int values;
    int count;

public:
    SudokuSquareSet()
        : values(0), count(0) {
    }

    int size() const {
        return count;
    }

    bool empty() const {
        return count==0;
    }

    void clear() {
        values = 0;
        count = 0;
    }

    bool operator==(const SudokuSquareSet other) {
        return (count==other.count && values==other.values);
    }

    bool operator!=(const SudokuSquareSet other) {
        return values!=other.values;
    }

    SudokuSquareIterator begin() const { 
        unsigned int copy = values;

        if (copy==0) return SudokuSquareIterator(values, 0);

        for (int i=0; i<25; i++) {
            if ((copy & 1)==1) {
                return SudokuSquareIterator(values, i);
            }
            copy = copy >> 1;
        }

        return SudokuSquareIterator(values, 0);
    }
        

    SudokuSquareIterator end() {
        return SudokuSquareIterator(values, -1);
    }

    SudokuSquareIterator insert(int value) {
        unsigned int mask = 0;
        if (value==0) {
            return end();
        } else {
            mask = 1;
            for (int i=1; i<value; i++) {
                mask = mask << 1;
            }
        }


        values = values | mask;
        count++;

        return SudokuSquareIterator(values, value);
    }

    SudokuSquareIterator find(int value) {
        unsigned int mask = 0;
        if (value==0) {
            return end();
        } else {
            mask = 1;
            for (int i=1; i<value; i++) {
                mask = mask << 1;
            }
        }

        mask = values & mask;
        return mask==0 ? end() : SudokuSquareIterator(values, value-1);
    }

    void erase(int value) {
        unsigned int mask = 0;
        if (find(value)==end()) return;
        if (value==0) {
            return;
        } else {
            mask = 1;
            for (int i=1; i<value; i++) {
                mask = mask << 1;
            }
        }

        mask = mask & 4294967295; // 32-bit max
        values = values ^ mask;
        count--;
    }

    void erase(SudokuSquareIterator &it) {
        erase(*it);
    }
};

// Do not write any code below this line
static_assert(sizeof(SudokuSquareSet) == sizeof(unsigned int) + sizeof(int), "The SudokuSquareSet class needs to have exactly two 'int' member variables, and no others");


#endif
