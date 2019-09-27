// insertionsort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <cmath>
using namespace std; 

void insertionSort(vector<int>& arrayToBeSorted, int low, int high);
void test(int testIndex, vector<int>& arrayToBeSorted);  // test each input size

int main()
{
	vector<int> testArray;  //  array will hold values for algo to computer of size  2^n 

	cout << "Insertion Sort algorithm with unsorted input" << endl;

	for (int i = 1; i <= 16; i++) // will loop through each test from 2-2^16
	{
		test(i, testArray);
		testArray.clear();
	}


}

void test(int testIndex, vector<int>& arrayToBeSorted)
{
	

	int powerForTesting = pow(2, testIndex); // creates test input size (2^n)

	for (int i = 0; i < powerForTesting; i++)
	{
		arrayToBeSorted.push_back(rand() % 100000); // creates array of size n with random numbers from 0 - 100000
	}

	if (powerForTesting <= 32 ) //prints unsorted array
	{
		cout << "Unsorted array of size " << powerForTesting << " before sorting" << endl;

		for (int i = 0; i <arrayToBeSorted.size(); i++)
		{
			cout << i + 1 << "." << arrayToBeSorted[i] << endl;
		}
	}

	cout << endl;

	cout << "Test " << testIndex << " with size of " << arrayToBeSorted.size() << endl;

	auto start = chrono::steady_clock::now(); // start timer

	insertionSort(arrayToBeSorted , 1, arrayToBeSorted.size()); // call insertionSort

	auto end = chrono::steady_clock::now(); // end timer
	auto diff = (end - start); // stores the difference of if the end and start time 
	cout << chrono::duration <double, milli>(diff).count() << " ms" << endl; // prints running time of insertion sort instance

	cout << endl;

	if (powerForTesting <= 32)  //prints sorted array
	{
		cout << "Sorted array of size " << powerForTesting << "after sorting " << endl;

		for (int i = 0; i < arrayToBeSorted.size(); i++)
		{
			cout << i + 1 << "." << arrayToBeSorted[i] << endl;
		}
	}

	cout << endl;
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