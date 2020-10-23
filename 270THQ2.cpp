/*
	CSCI 270 Fall 2018
	THQ1 Question 2
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

//This is only pseudocode, however it should be very close to compilable c++ code.
//The function maximize1 is the fully recursive solution
//The function maximize2 along with some work done in main is the interative version
//The iterative version runs in O(n^3) time, O(n^2) for the nested for loops in main, and for each of those there is O(n) work done in maximize2, giving O(n^3)

int OPT[(n/2) + 1][(n/2) + 1];	//This only holds numbers as we find optimal value, not the operators. Highest solution from i to j (first dimension index to the second dimension index)
int A[n];			//We are given an array A of size N, where N is odd. Odd numbered indexes are positive numbers, even indexes are + or *
int Num[(n/2) + 1];	//This is the array to hold all the positive numbers in A[]
int Opp[(n/2)];	//This is the array to hold all the operators in A[]

int main()
{
	int maxValue = 0;
	
	//We want to find the optimal way to use parthensises to maximize the array evaluation

	//Lets describe the subproblem
	//We need to find the maximum value of A[i up to k] (either * or +) the maximum value of A[k+1 -> j]
	//So we need to calculate this with k varying from i to j which is O(n)
	//There are Theta(n^2) substring of n, and so there are n^2 of these subproblems we need to do
	//As I said, we vary k from i to j (from the first index to the last index of what we are looking at) or O(n) work per subproblem.
	//Thus this is a O(n^2) * O(n) = O(n^3) solution.

	for(int i = 1, j = 1; i <= n; i+=2, j++){
		if(i % 2 == 1){	//for odd indexes (positive numbers)
			Num[j] = A[i];	//Put only odd indexes (positive numbers) in Num[]
		}
	}
	for(int i = 2, j = 1; i <= n; i+=2, j++){
		if(i % 2 == 0){	//for even indexes (operators)
			Opp[j] = A[i];	//Put only even indexes (operators) in Opp[]
		}
	}
	
	for (int i = 1; i <= Num.size(); i++) {	//The optimal value that only includes one number is that number
		OPT[i][i] = Num[i];
	}
	
	//We increase by 2 because we want to go from one even index to another for every even index to every other even index because we want to find maximum from one integer to another, we shouldn't start or end with a + or *
	for (int i = 1; i < Num.size(); i++) {	//We have double nested for loops which gives us O(n^2) for this case
		for (int j = 1; j < n - i; n++) 
			// While I is constant, j goes from 0 to n - i
			//We make k = j + i so that we have all pairs of i and j so that we have k - j = i, and thus fill up diagonals of OPT
			k = i + j;
			OPT[i][j] = maximize2(j, k);
		}
	}

	//The code fills in OPT from the diagonal [1][1] to [Num.size()][Num.size()] and then up one diagonal per loop, and that then puts the solution in the top right index, which is [1,n]

	maxValue = OPT[1][Num.size()];	//We set maxValue to the maximum value of OPT[1][n] because that is where I have stored the maximum value (top right corner, so the last diagonal to be filled in is just the top right index [1, N])

	return 0;
}

double maximize1(int a, j) {	//This is not dynamic programming version, it is expontential time, but is the recursive version.
	if (isDigit(A[0]) {			//If all when have is a digit and nothing else, then there must be a number at the 0th index. So if there is we will obviously return this value
		return A[0];
	}
	double ans = 0;

	for (int i = a; i < j; i++) {
		if (A[i] == '+') {
			ans = max(ans, maximize1[a][i - 1] + maximize1[i + 1][j]);	
		}
		if (A[i] == '*') {
			ans = max(ans, maximize1[a][i - 1] * maximize1[i + 1][j]);
		}
	}
	return ans;
}

double maximize2(int i, int j) {

	//Here is the code, it does the linear work from i to j = O(n)
	//We above selected i and j so that it would fill in diagonals of the 2D array
	//When finding the max of i to j we want to already know max from i to k and from k+1 to j.
	
	
	double maximum = 0;			//Finds the maximum that can be formed between indexes i and j, and we start with the diagonal from top right to bottom left filled in from above
	for (int var = i; var < j; i++) {
		if (A[var] == '+') {
			maximmum = max(maximum, OPT[i][var] + OPT[var + 1][j]);
		}
		else if (A[var] == "*") {
			maximmum = max(maximum, OPT[i][var] * OPT[var + 1][j]);
		}
	}
	return maximum;
}