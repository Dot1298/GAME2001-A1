#pragma once
#include <cassert>
#include <cstring>

template<class T>
class Array {
public:
    // Constructor
    Array(int size, int growBy = 1) :
        m_array(nullptr), m_maxSize(size), m_growSize(growBy), m_numElements(0) {
        if (size > 0) { // Is this a legal size for an array?
            m_array = new T[m_maxSize]; // Dynamically allocating an array to m_maxSize
            memset(m_array, 0, sizeof(T) * m_maxSize); // Explicitly set 0 to all elements in the array
        }
    }

    // Destructor
    virtual ~Array() {
        if (m_array != nullptr) {
            delete[] m_array;
            m_array = nullptr;
        }
    }

    virtual void push(T val) = 0;

    // Deletion (2 ways)
    // Remove the last item inserted into the array
    void pop() {
        if (m_numElements > 0) {
            m_numElements--; // Reduce the total number of elements by 1, ignoring the last element
        }
    }

    // Remove an item given an index
    // (Almost) Brute-force execution -- Big-O = O(N)
    void remove(int index) {
        assert(m_array != nullptr);
        if (index >= m_numElements) {
            // I am trying to remove something outside of the bounds of the array
            return; // <-- Maybe could do some form of exception handling
        }
        for (int i = index; i < m_numElements - 1; i++) {
            // Start at the index we want to remove.
            // Shift everything after index back by one.
            m_array[i] = m_array[i + 1];
        }
        m_numElements--;
    }

    // Searching
    // Binary Search
    int search(T searchKey)
    {
        assert(m_array != nullptr);

        // Helper variables.
        int lowerBound = 0;
        int upperBound = m_numElements - 1;
        int current = 0;

        while (1)	// <-- Replaced with recursion
        {
            current = (lowerBound + upperBound) >> 1;	//bitwise operation; divides by 2

            // Binary search steps:
            // Step 1: Check if the middle is the value we are looking for.
            if (m_array[current] == searchKey)
            {
                // Found the item in the middle of the array. Return the index
                return current;
            }
            // Step 2: Check that we've exhausted all options. Can't find the item
            else if (lowerBound > upperBound)
            {
                return -1;
            }
            // Step 3: Check which half of the array the value is in.
            else
            {
                if (m_array[current] < searchKey)
                {
                    lowerBound = current + 1;	// Value may be in the upper half
                }
                else
                {
                    upperBound = current - 1;	// Value may be in the lower half
                }
            }
        }

        return -1;	// Catch all return from danger.
    }

    // Overloaded [] operator
    T& operator[](int index) {
        assert(m_array != nullptr && index < m_numElements); // Null and out of bounds check
        return m_array[index];
    }

    // Clear
    void clear() {
        m_numElements = 0; // Ignore or forgets all current items in the array
    }

    // Gets and Sets
    int GetSize() const {
        return m_numElements;
    }
    int GetMaxSize() const {
        return m_maxSize;
    }
    int GetGrowSize() const {
        return m_growSize;
    }
    void SetGrowSize(int val) {
        assert(val >= 0);
        m_growSize = val;
    }

protected:
    // Private functions
    // Expansion
    bool Expand() {
        //if (m_growSize <= 0) {
        //    // LEAVE!
        //    return false;
        //}

        if (m_maxSize == 0) {
            m_maxSize = 2; 
        }
        else {
            m_maxSize *= 2; 
        }

        // Create the new array
        T* temp = new T[m_maxSize];
        assert(temp != nullptr);

        // Copy the contents of original array into the new array
        memcpy(temp, m_array, sizeof(T) * m_maxSize);

        // Delete the old array
        delete[] m_array;

        // Clean up variable assignments
        m_array = temp;

        std::cout << "Array expanded: new size = " << m_maxSize << std::endl;

        return true;
    }

    // Private Variables
    T* m_array; // Pointer to the beginning of the array
    int m_maxSize; // Maximum size of the array
    int m_growSize; // Amount the array can grow through expansion
    int m_numElements; // Number of items currently in my array

};
