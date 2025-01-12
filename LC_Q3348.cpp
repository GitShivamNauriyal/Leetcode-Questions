#include <bits/stdc++.h>
// #include <iostream>
// #include <unordered_map>
// #include <string>

class Solution {
public:
	string smallestNumber(string num, long long t) {
		// Calculate prime factorization of t and check divisibility
		const auto [primeCount, isDivisible] = getPrimeCount(t);
		if (!isDivisible)
			return "-1";

		// Calculate required factor count for t
		const unordered_map<int, int> factorCount = getFactorCount(primeCount);
		if (sumValues(factorCount) > num.length())
			return construct(factorCount);

		// Calculate prime factor count for prefix of num
		unordered_map<int, int> primeCountPrefix = getPrimeCount(num);
		int firstZeroIndex = num.find('0');
		if (firstZeroIndex == string::npos) {
			firstZeroIndex = num.length();
			if (isSubset(primeCount, primeCountPrefix))
				return num;
		}

		// Attempt to replace digits with larger ones to maintain divisibility
		for (int i = num.length() - 1; i >= 0; --i) {
			const int d = num[i] - '0';
			primeCountPrefix = subtract(primeCountPrefix, kFactorCounts.at(d));
			const int spaceAfterThisDigit = num.length() - 1 - i;
			if (i > firstZeroIndex)
				continue;
			for (int biggerDigit = d + 1; biggerDigit < 10; ++biggerDigit) {
				const unordered_map<int, int> factorsAfterReplacement =
				    getFactorCount(subtract(subtract(primeCount, primeCountPrefix),
				                            kFactorCounts.at(biggerDigit)));
				if (sumValues(factorsAfterReplacement) <= spaceAfterThisDigit) {
					const int fillOnes =
					    spaceAfterThisDigit - sumValues(factorsAfterReplacement);
					return num.substr(0, i) +
					       to_string(biggerDigit) +
					       string(fillOnes, '1') +
					       construct(factorsAfterReplacement);
				}
			}
		}

		// Extend the number if no solution was found in the loop
		const unordered_map<int, int> factorsAfterExtension =
		    getFactorCount(primeCount);
		return string(num.length() + 1 - sumValues(factorsAfterExtension), '1') +
		       construct(factorsAfterExtension);
	}

private:
	constexpr static unordered_map<int, unordered_map<int, int>> kFactorCounts = {
		{0, {}},       {1, {}},       {2, {{2, 1}}},         {3, {{3, 1}}},
		{4, {{2, 2}}}, {5, {{5, 1}}}, {6, {{2, 1}, {3, 1}}}, {7, {{7, 1}}},
		{8, {{2, 3}}}, {9, {{3, 2}}}
	};

	// Get prime factorization count for a number
	pair<unordered_map<int, int>, bool> getPrimeCount(long long t) {
		unordered_map<int, int> count{{2, 0}, {3, 0}, {5, 0}, {7, 0}};
		for (const int prime : {
		            2, 3, 5, 7
		        }) {
			while (t % prime == 0) {
				t /= prime;
				++count[prime];
			}
		}
		return {count, t == 1};
	}

	// Get prime factorization count for a string of digits
	unordered_map<int, int> getPrimeCount(const string& num) {
		unordered_map<int, int> count{{2, 0}, {3, 0}, {5, 0}, {7, 0}};
		for (const char d : num)
			for (const auto& [prime, freq] : kFactorCounts.at(d - '0'))
				count[prime] += freq;
		return count;
	}

	// Translate prime factor counts to specific digit counts
	unordered_map<int, int> getFactorCount(const unordered_map<int, int>& count) {
		unordered_map<int, int> res;
		const int count8 = count.at(2) / 3;
		const int remaining2 = count.at(2) % 3;
		const int count9 = count.at(3) / 2;
		int count3 = count.at(3) % 2;
		int count4 = remaining2 / 2;
		int count2 = remaining2 % 2;
		int count6 = 0;
		if (count2 == 1 && count3 == 1) {
			count2 = 0;
			count3 = 0;
			count6 = 1;
		}
		if (count3 == 1 && count4 == 1) {
			count2 = 1;
			count6 = 1;
			count3 = 0;
			count4 = 0;
		}
		return unordered_map<int, int> {
			{2, count2}, {3, count3},      {4, count4}, {5, count.at(5)},
			{6, count6}, {7, count.at(7)}, {8, count8}, {9, count9}
		};
	}

	// Construct a string representation from digit factors
	string construct(const unordered_map<int, int>& factors) {
		string res;
		for (int digit = 2; digit < 10; ++digit)
			res += string(factors.at(digit), '0' + digit);
		return res;
	}

	// Check if all elements in `a` are covered by `b`
	bool isSubset(const unordered_map<int, int>& a,
	              const unordered_map<int, int>& b) {
		for (const auto& [key, value] : a)
			if (b.at(key) < value)
				return false;
		return true;
	}

	// Subtract values of `b` from `a`
	unordered_map<int, int> subtract(unordered_map<int, int> a,
	                                 const unordered_map<int, int>& b) {
		for (const auto& [key, value] : b)
			a[key] = max(0, a[key] - value);
		return a;
	}

	// Sum all values in the unordered map
	int sumValues(const unordered_map<int, int>& count) {
		return accumulate(count.begin(), count.end(), 0,
		[](int subtotal, const pair<int, int>& p) {
			return subtotal + p.second;
		});
	}
};


int main()
{
	std::cout<<"Hello World\n";
	
	Solution solution;
	cout << solution.smallestNumber("1234", 256) << "\n";

	return 0;
}