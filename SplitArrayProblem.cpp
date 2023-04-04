#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_set>

using namespace std;

bool isPossible(int len, int sum)
/*
sum(B) / len(B) = sum(C) / len(C) = [sum(A) - sum(B)] / [len(A) - len(B)]
sum(B) * [len(A) - len(B)] = [sum(A) - sum(B)] * len(B)
sum(B) * len(A) - sum(B) * len(B) = sum(A) * len(B) - sum(B) * len(B)
sum(B) * len(A) = sum(A) * len(B)
sum(B) = [sum(A) * len(B)] / len(A)

sum(B) is an integer => for a possible split, sum(A) * i % len(A) == 0 for at least one value of i
i from 1 to len(B)
len(B) from 1 to len(A) - 1
*/
{
	if (len < 2)
		return false;

	for (int i = 1; i < len / 2; i++)
		if (sum * i % len == 0) return true;
	return false;
}

bool splitArray(vector<int>& A)
{
	int len = A.size();
	int sum = accumulate(A.begin(), A.end(), 0);

	if (isPossible(len, sum) == false)
		return false;

	vector<unordered_set<int>> partialSums(len / 2 + 1);
	partialSums[0].insert(0);

	for (int a : A)
		for (int i = len / 2; i >= 1; i--)
			for (int k : partialSums[i - 1])
				partialSums[i].insert(a + k);

	for (int i = 1; i < len / 2; i++)
		if (sum * i % len == 0 && partialSums[i].find(sum * i / len) != partialSums[i].end())
			return true;

	return false;
}

int main()
{
	vector<int> v = { 1,2,3,4,5,6,7,8 };
	cout << splitArray(v);
}
