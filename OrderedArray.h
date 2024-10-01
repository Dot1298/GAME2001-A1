#pragma once
#include "Array.h"

template<class T>
class OrderedArray : public Array<T> {
public:
    // Constructor 
    OrderedArray(int size, int growBy = 1) : Array<T>(size, growBy) {}

    // Insertion -- Big-O = O(N)
    void push(T val) override {
        assert(this->m_array != nullptr);

        //Duplicate check******************************************
        if (this->search(val) != -1) {
            return; 
        }

        if (this->m_numElements >= this->m_maxSize) {
            this->Expand();
        }

        int i;
        // Step 1: Find the index to insert val
        for (i = 0; i < this->m_numElements; i++) {
            if (this->m_array[i] > val) {
                break;
            }
        }

        // Step 2: Shift everything to the right of the index(i) forward by one. Work backwards
        for (int k = this->m_numElements; k > i; k--)
        {
            this->m_array[k] = this->m_array[k - 1];
        }

        // Step 3: Insert val into the array at index
        this->m_array[i] = val;
        this->m_numElements++;

        // return i;
    }
};
