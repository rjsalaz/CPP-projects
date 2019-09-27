// Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <vector> 
#include <algorithm>
#include <queue>
using namespace std; 



// create class for items 
class Items
{
	private:

		int weight;
		int price; 
		int weight_price_ratio; 
		int include; 
		int bestSet; 

		void setRatio()
		{
			if (getPrice() == 0 && getWeight() == 0)
			{
				weight_price_ratio = 0;
			}
			else
			{
				weight_price_ratio = price / weight;
			}
		}

	public: 

		// constructor // 
		Items(int item_weight, int item_price)
		{
			setWeight(item_weight);
			setPrice(item_price);

			if (item_price == 0 && item_weight == 0)
			{
				weight_price_ratio = 0;
			}
			else
			{

				weight_price_ratio = item_price / item_weight;
			}
		}

		///////////////////////////////getters//////////////////////////////////////

		int getWeight()
		{
			return weight;

		}

		int getPrice()
		{

			return price; 

		}

		int getRatio()
		{
			return weight_price_ratio; 
		}

		int getBestSet()
		{
			return bestSet; 

		}

		int getInclude()
		{
			return include; 
		}
		

		/////////////////////////////// setters //////////////////////////////////
		void setInclude(int yes_or_no)
		{
			include = yes_or_no; 
		}

		void setBestSet(int best)
		{
			bestSet = best;
		}
		void setWeight(int item_weight)
		{
			weight = item_weight; 
		}

		void setPrice(int item_price)
		{
			price = item_price; 

		}

};

// class for nodes used  for branch and bound 
class nodes
{	public: 
		int level;
		int profit;
		int weight; 
		int bound; 
		int visited;
	
	
};
// operator will force priority queue to sort by the bound of each node in queue
bool operator<(nodes const& b1, nodes const& b2)
{
			// return "true" if "p1" is ordered  
			// before "p2", for example: 
	return b1.bound < b2.bound;
}

	

//////////////////////////// global variables //////////////////////////////////

vector<Items> items;		// item class to be used in each algorithm
int maxProfit = 0;			// initial max profit 
int maxWeight = 0;			// initial weight capacity of bag 
int backtrackNodes = 0;		// number of nodes visited in backtrack algorithm 
int bruteNodes = 0;			// number of nodes visited in brute force algorithm 
int branAndBoundNodes = 0;  // number of nodes visited in branch and bound algorithm 

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////functions//////////////////////////////////////
int getInput();
void sortByRatio();

void backtrack(int index);
void knapsack(int profit, int weight, int index, vector<string> &include, vector<string> &bestSet);
bool promising(int index, int profit, int weight);

void branchAndBound();
void knapsack3();
int bound(nodes u);

void bruteKnap(int price, int weight, int index, vector<string> &include, vector<string> &bestSet);
bool brutePromising(int index, int price, int weight);
void bruteForce(int index);

///////////////////////////////////////////////////////////////////////////////////////


int main()
{
	int index; 

	// get user input 
	index = getInput(); 

	// Sort items by ratio 
	sortByRatio();

	// Call branch and bound 
	branchAndBound();

	//reset max profit 0 
	maxProfit = 0; 


	// call backtrack 
	backtrack(index);

	// reset max profit to 0 
	maxProfit = 0;

	// call brute force 
	bruteForce(index);

}


int getInput()
{
	int numOfItems = 0;
	int index = 0;


	//get number of items to be places in bag
	cout << "How many item are there going to be: ";
	cin >> numOfItems;
	cout << endl;


	// make room for and store dummy node 
	numOfItems++;
	items.push_back(Items(0, 0));


	//build each item by getting it weight and price then store item into vector 
	for (int i = 1; i < numOfItems; i++)
	{
		int weight;
		int price;

		cout << "What is item " << i << "'s weight: ";
		cin >> weight;

		cout << "What is item " << i << "'s price: ";
		cin >> price;

		items.push_back(Items(weight, price));

		cout << endl;
	}


	cout << endl;


	// get max weight of the bag
	cout << "What is the max weight of the bag: ";
	cin >> maxWeight;
	cout << endl << endl;

	return index;
}
void sortByRatio()
{


	// sort vector by ratio
	sort(items.begin() + 1, items.end(), [](Items  a, Items  b)
	{
		return a.getRatio() > b.getRatio();
	});

	cout << "*************** Items Sorted by Ratio **************" << endl;
	for (int i = 1; i < items.size(); i++)
	{
		cout << "Item " << i << "'s weight: " << items[i].getWeight() << ", Price: " << items[i].getPrice() << ", ratio: " << items[i].getRatio() << endl;

	}




}


////////////////////////////////////////////////// Backtrack /////////////////////////////////////////////////


void backtrack(int index)
{	// vector used to find the best path 
	vector<string>include(items.size());
	vector<string>bestSet(items.size());

	//call knapsack using backtracking 
	knapsack(items[index].getPrice(), items[index].getWeight(), index, include, bestSet);

	cout << "****************** Backtracking Solution *****************" << endl;
	cout << "Best profit : " << maxProfit;

	cout << endl << endl;

	//print optimal path (items taken)  
	cout << "Items Taken: ";
	for (int i = 1; i < bestSet.size(); i++)
	{
		if (bestSet[i] == "yes")
		{
			cout << "Item " << i << " ";
		}
	}

	cout << endl << endl;

	// print items not taken 
	cout << "Items not Taken: ";
	for (int i = 1; i < bestSet.size(); i++)
	{
		if (bestSet[i] != "yes")
		{
			cout << "Item " << i << " ";
		}
	}

	cout << endl << endl;

	//number of nodes visited 
	cout << "Number of Nodes Visited: " << backtrackNodes;
	cout << endl << endl;

	cout << "***********************************************************" << endl;
	cout << endl << endl;
}

void knapsack( int price, int weight, int index, vector<string> &include, vector<string> &bestSet)
{
	backtrackNodes++; // keep count of the number of nodes visited

	if (weight <= maxWeight && price > maxProfit)
	{
		maxProfit = price ;


		bestSet = include;
		
	}

	if (promising( index, price, weight ) )
	{

		
		include[index + 1] = "yes";
 	       // knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
		knapsack( ( price + items[index + 1].getPrice() ), ( weight + items[index + 1].getWeight() ),( index + 1 ), include, bestSet);

		include[index + 1] = "no";
	       // knapsack(i + 1, profit, weight);
		knapsack(price , weight, (index + 1), include, bestSet);

	}

}

bool promising( int index, int price, int weight )
{
	int j;
	int k;
	int totalWeight;
	double bound; 
	

	if (weight >= maxWeight)
	{

		return false; 

	}
	else
	{

		j = index + 1; 

		bound = price ;

		totalWeight = weight; 


		while ( j <= ( items.size() - 1 ) && ( totalWeight + items[j].getWeight() ) <= maxWeight)
		{
			totalWeight = totalWeight + items[j].getWeight();

			bound = bound + items[j].getPrice();

			j++;

		}

		k = j; 

		if ( k <= ( items.size() - 1) ) 
		{
			bound = bound + (maxWeight - totalWeight) * items[k].getRatio(); 

		}

		return bound > maxProfit;
	}


}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////// Branch and Bound ///////////////////////////////////////////


void branchAndBound()
{
	knapsack3();


	cout << "**************** Branch and Bound Solution ****************" << endl;
	cout << "Best profit : " << maxProfit;

	cout << endl << endl;

	// print number of nodes visited 
	cout << "Number of Nodes Visited: " << branAndBoundNodes;
	cout << endl << endl;

	cout << "************************************************************" << endl;
}

void knapsack3()
{
	// create nodes and initialize queue 
	nodes u;
    nodes v;
	priority_queue <nodes>  queue;
	

	// set dummy node 
	v.level = 0; 
	v.profit = 0;
	v.weight = 0;
	maxProfit = 0;
	v.bound = bound(v); 

	branAndBoundNodes++;

	queue.push(v);

	while (!queue.empty())
	{
		 
		v = queue.top();
		queue.pop();


		if (v.bound > maxProfit)
		{

			u.level = v.level + 1;
			u.weight = v.weight + items[u.level].getWeight();
			u.profit = v.profit + items[u.level].getPrice(); 
			u.bound = bound(u);
			branAndBoundNodes++;

			if (u.weight <= maxWeight && u.profit > maxProfit)
			{
				maxProfit = u.profit; 

			}


			if (u.bound > maxProfit)
			{
				queue.push(u);
				
			}


			u.weight = v.weight;
			u.profit = v.profit;
			u.bound = bound(u);
			branAndBoundNodes++;

			if (u.bound > maxProfit)
			{
				queue.push(u);
			
			
			}
		


		}
	}

}

int bound(nodes u)
{
	int j;
	int k;

	int totweight;
	int result;
	if (u.weight >= maxWeight)
	{
		return 0;

	}
	else
	{

		result = u.profit;
		j = u.level + 1;
		totweight = u.weight;

		while (j <= (items.size() - 1) && (totweight + items[j].getWeight()) <= maxWeight)
		{
			totweight = totweight + items[j].getWeight();
			result = result + items[j].getPrice();
			j++;

		}

		k = j;

		if (k <= (items.size() - 1))
		{
			result = result + (maxWeight - totweight) * items[k].getRatio();
		}

		return result;

	}


}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////// Brute force///////////////////////////////////////////////

void bruteForce(int index)
{
	// vectors used to find the best path 
	vector<string>include(items.size());
	vector<string>bestSet(items.size());

	bruteKnap(items[index].getPrice(), items[index].getWeight(), index, include, bestSet);

	cout << "****************** Brute Force Solution *****************" << endl;
	cout << "Best profit : " << maxProfit;

	cout << endl << endl;


	// print optimal path (items taken) 
	cout << "Items Taken: ";
	for (int i = 1; i < bestSet.size(); i++)
	{
		if (bestSet[i] == "yes")
		{
			cout << "Item " << i << " ";
		}
	}

	cout << endl << endl;
	 
	// print items not taken 
	cout << "Items not Taken: ";
	for (int i = 1; i < bestSet.size(); i++)
	{
		if (bestSet[i] != "yes")
		{
			cout << "Item " << i << " ";
		}
	}

	cout << endl << endl;

	// print number of nodes visited 
	cout << "Number of Nodes Visited: " << bruteNodes + 1;
	cout << endl << endl;

	cout << "***********************************************************" << endl;
	cout << endl << endl;



}

void bruteKnap(int price, int weight, int index, vector<string> &include, vector<string> &bestSet )
{	
	bruteNodes++;
	 
	if (weight <= maxWeight && price > maxProfit)
	{
		maxProfit = price;


		bestSet = include;

	}

	if ((brutePromising(index, price, weight)))
	{

		include[index + 1] = "yes";
		// knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
		bruteKnap((price + items[index + 1].getPrice()), (weight + items[index + 1].getWeight()), (index + 1), include, bestSet);

		include[index + 1] = "no";
		// knapsack(i + 1, profit, weight);
		bruteKnap(price, weight, (index + 1), include, bestSet);

	}
}

 bool brutePromising( int index, int price, int weight)
{
	bruteNodes++;
	int j;
	int k;
	int totalWeight;
	double bound;


	if ( ( index + 1 ) > ( items.size()- 1) )
	{

		return false;

	}
	else
	{

		j = index + 1;

		bound = price;

		totalWeight = weight; 


		while (j <= (items.size() - 1) && (totalWeight + items[j].getWeight()) <= maxWeight)
		{
			totalWeight = totalWeight + items[j].getWeight();

			bound = bound + items[j].getPrice();

			j++;

		}

		k = j;

		if (k <= (items.size() - 1))
		{
			bound = bound + (maxWeight - totalWeight) * items[k].getRatio();

		}

		return bound > maxProfit;
	}
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////



