// mergesort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <cmath>
using namespace std;

void mergesort(vector<int>& arrayToBeSorted);
void merge(vector<int>& leftArray, vector<int>& rightArray, vector<int>& arrayToBeSorted);
void test(int testIndex, vector<int>& arrayToBeSorted);  // test each input size

int main()
{

	vector<int> testArray;  //  array will hold values for algo to computer of size  2^n 

	cout << "Merge Sort algorithm with unsorted input" << endl;

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

	if (powerForTesting <= 32)//prints unsorted array
	{
		cout << "Unsorted array of size " << powerForTesting <<" before sorting"<< endl;

		for (int i = 0; i < arrayToBeSorted.size(); i++)
		{

			cout << i + 1 << "." << arrayToBeSorted[i]<< endl;
		}
	}
	
	cout << endl;

	cout << "Test " << testIndex << " with size of " << arrayToBeSorted.size() << endl;
	auto start = chrono::steady_clock::now(); // start timer

	mergesort(arrayToBeSorted); // call mergesort 

	auto end = chrono::steady_clock::now(); // end timer
	auto diff = (end - start); // stores the difference of the end and start time 
	cout << chrono::duration <double, milli>(diff).count() << " ms" << endl; // prints running time of merge sort instance

	cout << endl;

	if (powerForTesting <= 32)  //prints sorted array
	{
		cout << "Sorted array of size " << powerForTesting <<"after sorting "<< endl;

		for (int i = 0; i < arrayToBeSorted.size(); i++)
		{
			cout << i + 1 << "." << arrayToBeSorted[i] << endl;
		}
	}

	cout << endl;
}

void mergesort(vector<int>& arrayToBeSorted)
{

	if (arrayToBeSorted.size() <= 1)
	{
		return;
	}
	else
	{

		int  leftLength = (arrayToBeSorted.size() / 2);

		int rightLength = ((arrayToBeSorted.size()) - (leftLength));

		vector<int> leftArray;
		vector<int> rightArray;

		leftArray.reserve(leftLength);
		rightArray.reserve(rightLength);


		for (int i = 0; i < leftLength; i++)
		{
			leftArray.push_back(arrayToBeSorted[i]);

		}

		for (int i = 0; i < (rightLength); i++)
		{
			rightArray.push_back(arrayToBeSorted[leftLength + i]);
		}


		mergesort(leftArray);
		mergesort(rightArray);
		merge(leftArray, rightArray, arrayToBeSorted);


	}

}

void merge(vector<int>& leftArray, vector<int>& rightArray, vector<int>& arrayToBeSorted)
{
	int leftLength = leftArray.size();
	int rightLength = rightArray.size();

	int i = 0;
	int j = 0;
	int k = 0;

	while (i < leftLength && j < rightLength)
	{
		if (leftArray[i] <= rightArray[j])
		{
			arrayToBeSorted[k] = leftArray[i];
			i++;
		}
		else
		{
			arrayToBeSorted[k] = rightArray[j];
			j++;
		}

		k++;
	}

	if (i < leftLength)
	{
		while (i < leftLength)
		{
			arrayToBeSorted[k] = leftArray[i];
			k++;
			i++;
		}

	}
	else
	{
		while (j < rightLength)
		{
			arrayToBeSorted[k] = rightArray[j];
			k++;
			j++;
		}
	}

}

