/*
	CSCI 270 Fall 2018
	THQ1 Question 1
	Name   :Christopher Pack
	Email  :cpack@usc.edu
	USC ID :3829084398
*/
#include "stdafx.h"
#include "iostream"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;


int F, B, S;
int G = 0;
// We know F,B,S are (though we arent given their actual values, it is a "known" value)
int b[B];	//Array of size B for all buses, lowercase b is array, uppercase B is number of students.
			//b[i] is the number of buses needed for project i
int s[S];	//Array of size S for all students, lowercase s is array, uppercase S is number of students
			//s[i] is the number of students needed for project i

int g[F];	//There are F projects, we hold the goodwill for each of the F projects in g at the projects index

int OPT[F][B][S] = nullptr;		//This is used for the dynamic programing function to save previously calculated values

int items[][];

int main()
{
	int maxGoodwill1 = 0;
	maxGoodwill1 = Goodwill1(F, S, B, G);	//Purely recursive way
	int maxGoodwill2 = 0;
	maxGoodwill2 = Goodwill2(F, S, B, G);	//Dynamic Programming way
	//Now try to recreate the items
	set<int> projects;
	projects = recreate(F, S, B);		//returns a set of projects (the indexes of the projects)
	for(auto element : projects){	//Print out each project taken
		cout << element << ", ";
	}
	cout << endl;
    return 0;
}

double Goodwill1(int i, int S, int B, int G) {	//This is recursive (slow) way, the Goodwill function below this will use dynamic programming 
	//First give recursive function

	//Base cases
	if (i == 0 || S == 0 || B == 0) {
		return 0;
		//If there are no more projects left, or if there are no students left, or if there are no buses left
		//Then no goodwill can be gained, 
	}

	if (s[i] > S) {				//Though maybe bad in practice, we keep s, b, and g global so we can alway access them
		return Goodwill1(i - 1, S, B, G);	//If this project takes more students than we have remaining, we don't take this project and keep recursing
	}
	
	if (b[i] > B) {
		return Goodwill1(i - 1, S, B, G);	//If this project takes more buses than we have remaining, we don't take this project and keep recursing
	}
	else {	//Else we recursively take the max of both us taking this ith project and not taking it
		return max(Goodwill1(i-1, S - s[i], B - b[i], G + g[i]), Goodwill1(i-1, S, B, G));
	}
}

double Goodwill2(int i, int S, int B, int G) {	//This is the dynamic programming version
	//Base cases
	
	if (OPT[i][S][B] != nullptr) {
		return OPT[i][S][B];
	}

	if (i == 0 || S == 0 || B == 0) {
		OPT[i][S][B] = 0;
		return 0;
		//If there are no more projects left, or if there are no students left, or if there are no buses left
		//Then no goodwill can be gained, 
	}

	if (s[i] > S) {				//Though maybe bad in practice, we keep s, b, and g global so we can alway access them
		int ans = Goodwill2(i - 1, S, B, G);	//If this project takes more students than we have remaining, we don't take this project and keep recursing
		OPT[I][S][B] = ans;
		return ans;
	}

	if (b[i] > B) {
		int ans = Goodwill2(i - 1, S, B, G);	//If this project takes more buses than we have remaining, we don't take this project and keep recursing
		OPT[I][S][B] = ans;
		return ans;
	}

	else {	//Else we recursively take the max of both us taking this ith project and not taking it and save the answer so we don't repeat the same computation again. (Memoization)
		max1 = Goodwill2(i - 1, S - s[i], B - b[i], G + g[i]);
		max2 = Goodwill2(i - 1, S, B, G);
		int ans = max(max1, max2);
		OPT[i][S][B] = ans;
		return ans;
	}
	
}
set<int> recreate(int F, int S, int B){	//OPT is global so dont need to pass it
	set<int> itemsTaken;				//Since this is all psuedocode I may not always be using actual c++ sytax, im just not sure and don't want to take the time
	for(int i = F; i > 0; i--){
		if(OPT[i][S][B] = OPT[i-1][S-s[i][B-B[i]){
			//Then we didn't take this project, optimal with it and without are the same
		}
		if(OPT[i][S][B] > OPT[i][S-s[i]][B-b[i]){	//Then the optimal we found with this project is greater than if we dont take it
			items.insert(i);
		}
	}
}
