#pragma once
#include "Array.h"

template<class T>
class UnorderedArray : public Array<T> {
public:
    // Constructor
    UnorderedArray(int size, int growBy = 1) : Array<T>(size, growBy) {}

    // Fast insertion for UnorderedArray -- Big-O is O(1)
    void push(T val) override {
        assert(this->m_array != nullptr); // Debugging purposes
        if (this->m_numElements >= this->m_maxSize) { // Check if the array has to expand to accommodate the new data
            this->Expand();
        }

        // My array has space for a new value. Let's add it!
        this->m_array[this->m_numElements] = val;
        this->m_numElements++;
    }
};
