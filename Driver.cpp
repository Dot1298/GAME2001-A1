#include <iostream>
//#include "UnorderedArray.h"
#include "OrderedArray.h"

using namespace std;

int main()
{
	//UnorderedArray<int> array(3);

	//array.push(3);
	//array.push(53);
	//array.push(83);
	//array.push(23); //Should call expand here
	//array.push(82); //Should call expand here
	//// 3, 23, 53, 82, 83
	//array[2] = 112;
	//// 3, 23, 112, 82, 83
	//array.pop();
	//// 3, 23, 112, 82
	//array.remove(2);
	//// 3, 23, 82

	//cout << "Ordered array contents: ";

	//for (int i = 0; i < array.GetSize(); i++)
	//{
	//	cout << array[i] << " ";
	//}

	//cout << endl;

	///////////////////////////////////////////////////////////

	OrderedArray<int> array(3);

	array.push(3);
	array.push(53);
	array.push(83);
	array.push(23); // Should expand here
	array.push(82); // Should expand here
	// 3, 23, 53, 82, 83
	
	//Attempted to add duplicate entries
	array.push(23);
	array.push(53);

	cout << "Ordered array contents: ";

	for (int i = 0; i < array.GetSize(); i++)
	{
		cout << array[i] << " ";
	}

	cout << endl;


	cout << "Search for 53 was found at index: ";
	cout << array.search(53) << endl; // -1
	cout << "Search for 23 was found at index: ";
	cout << array.search(23) << endl; // 1
}