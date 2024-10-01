#pragma once
#include <cassert>

template<class T>
class UnorderedArray
{
public:
	// Constructor
	UnorderedArray(int size, int growBy = 1) :
		m_array(NULL), m_maxSize(0), m_growSize(0), m_numElements(0)
	{
		if (size) //Is this a legal size of an array?
		{
			m_maxSize = size;
			m_array = new T[m_maxSize]; //Dynamically allocating an array to m_maxSize
			memset(m_array, 0, sizeof(T) * m_maxSize); // Explicitly set 0 to all elements in the array

			m_growSize = ((growBy > 0) ? growBy : 0);
		}
	}

	// Destructor
	~UnorderedArray()
	{
		if (m_array != nullptr)
		{
			delete[] m_array;
			m_array = nullptr;
		}
	}

	// Insertion
	// Fast insertion for UnorderedArray -- Big-O is O(1)
	void push(T val)
	{
		assert(m_array != nullptr); // Debugging purposes
		if (m_numElements >= m_maxSize) // Check if the array has to expand to accomodate the new data
		{
			Expand();
		}

		//My array has space for a new value. Let's add it!
		m_array[m_numElements] = val;
		m_numElements++;
	}

	// Deletion (2 ways)
	// Remove the last item inserted into the array
	void pop()
	{
		if (m_numElements > 0)
		{
			m_numElements--; //Reduce the total number of elements by 1, ignoring the last element
		}
	}

	// Remove an item given an index
	// (Almost) Brute-force execution -- Big-O = O(N)
	void remove(int index)
	{
		assert(m_array != nullptr);

		if (index >= m_numElements)
		{
			//I am trying to remove something outside of the bounds
			return; //Maybe some exception handling
		}
		for (int i = index; i < m_numElements; i++)
		{
			//Start at the index we want to remove
			//Shift everything after index back by one
			if (i + 1 < m_numElements) // confines the loop into the array
			{
				m_array[i] = m_array[i + 1];
			}
		}
		m_numElements--;
	}

	// Searching
	// Linear 
	int search(T val)
	{
		assert(m_array != nullptr);

		//Brute force search
		for (int i = 0; i < m_numElements; i++)
		{
			if (m_array[i] == val)
			{
				return i; //Return th eindex of where the item is located in the array
			}
		}
		return -1; //Index not found
	}

	// Overloaded [] operator
	T& operator[](int index)
	{
		assert(m_array != nullptr && index < m_numElements); //Null and out of bounds check
		return m_array[index];
	}

	// Clear
	void clear()
	{
		m_numElements = 0; //Ignore or forgets all current items in the array
	}

	// Gets and Sets
	int GetSize()
	{
		return m_numElements;
	}
	int GetMaxSize()
	{
		return m_maxSize;
	}
	int GetGrowSize()
	{
		return m_growSize;
	}
	void SetGrowSize(int val)
	{
		assert(val >= 0);
		m_growSize = val;
	}

private:
	// Private functions
		// Expansion
	bool Expand()
	{
		if (m_growSize <= 0)
		{
			//Leave!
			return false;
		}

		//Create the new array
		T* temp = new T[m_maxSize + m_growSize];
		assert(temp != nullptr);

		//Copy the contents of original array into the new array
		memcpy(temp, m_array, sizeof(T) * m_maxSize);

		//Delete the old array
		delete[] m_array;

		//Clean up variable assignments
		m_array = temp;
		temp = nullptr;

		m_maxSize += m_growSize;

		return true;
	}

private:
	// Private Variables
	T* m_array; //Pointer to the beginning of the array

	int m_maxSize; // Max size of the array
	int m_growSize; //Amount the array can grow through expansion
	int m_numElements; // Number of items currently in my array

};