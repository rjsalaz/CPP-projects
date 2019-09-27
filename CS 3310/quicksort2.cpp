// quicksort2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <cmath>
using namespace std; 


void quicksort2(int low, int high, vector<int>& arrayToBeSorted);
void insertionSort(vector<int>& arrayToBeSorted, int low, int high);
void partition(int low, int high, int& piviotPoint, vector<int>& arrayToBeSorted);
void test(int testIndex, vector<int>& arrayToBeSorted); // test each input size

int main()
{

	cout << "Quick sort 2 algorithm with unsorted input" << endl;
	vector<int> testArray;  //  array will hold values for algo to computer of size  2^n 

	for (int i = 1; i <= 16; i++) // will loop through each test from 2-2^16
	{
		test(i,testArray);
		testArray.clear(); 
	}

}


void test(int testIndex, vector<int>& arrayToBeSorted) 
{
	int powerForTesting= pow(2, testIndex); // limit of test (2^)

	for (  int i = 0 ; i < powerForTesting; i++)
	{
		arrayToBeSorted.push_back(rand() % 100000); // creates array of size n with random numbers from 0 - 100000
	}

	if (powerForTesting <= 32)//prints unsorted array
	{
		cout << "Unsorted array of size " << powerForTesting << " before sorting" << endl;

		for (int i = 0; i < arrayToBeSorted.size(); i++)
		{
			cout << i + 1 << "." << arrayToBeSorted[i] << endl;
		}
	}

	cout << endl;

	cout << "Test " << testIndex << " with size of " << arrayToBeSorted.size() << endl;
	auto start = chrono::steady_clock::now(); // start timers 

	quicksort2(1, arrayToBeSorted.size() - 1, arrayToBeSorted); // call quick sort 

	auto end = chrono::steady_clock::now(); // end timer
	auto diff = (end - start); // stores the difference of if the end and start time 
	cout << chrono::duration <double, milli>(diff).count() << " ms" << endl; // prints running time of quick sort instance

	cout << endl;

	if (powerForTesting <= 32)
	{
		cout << "Sorted array of size " << powerForTesting << " after sorting "<< endl;

		for (int i = 0; i < arrayToBeSorted.size(); i++)
		{
			cout << i + 1 << "." << arrayToBeSorted[i] << endl;
		}
	}

	cout << endl;
}

void quicksort2(int low, int high, vector<int>& arrayToBeSorted)
{
	int piviotPoint;

	if(high > low)
	{		

			if ((high - low) <= 16)
			{
				insertionSort(arrayToBeSorted, low, high + 1 );
			}
			else
			{
				partition(low, high, piviotPoint, (arrayToBeSorted));
				quicksort2(low, piviotPoint - 1, arrayToBeSorted);
				quicksort2(piviotPoint + 1, high, arrayToBeSorted);
			}
	}
}


void insertionSort(vector<int>& arrayToBeSorted, int low, int high)
{
	int valToBeSorted;
	int j;



	for (int i = low; i < high; i++)
	{
		valToBeSorted = arrayToBeSorted[i];
		j = i - 1;
		
		while ((j >= 0) && arrayToBeSorted[j] > valToBeSorted)
		{
			arrayToBeSorted[j + 1] = arrayToBeSorted[j];
			j--;
		}

		arrayToBeSorted[j + 1] = valToBeSorted;
	}

}


void partition(int low, int high, int& piviotPoint, vector<int>& arrayToBeSorted)
{
	int i;
	int j;


	int piviotItem = arrayToBeSorted[low];

	j = low;

	for (i = (low + 1); i <= high; i++)
	{
		if (arrayToBeSorted[i] < piviotItem)
		{
			j++;
			swap(arrayToBeSorted[i], arrayToBeSorted[j]);
		}
	}

	piviotPoint = j;
	swap(arrayToBeSorted[low], arrayToBeSorted[piviotPoint]);

}