#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

// client interface
bool knapsackHelper(const map<string, int>& items, int limit, vector<string>& curr, int minW){
	if(minW > limit){
		return true;
	}
	else{
		for(auto i : items){
			if((limit - i.second) >= 0){
				vector<string> currTemp = curr;
				currTemp.push_back(i.first);
				return knapsackHelper(items, limit - i.second, currTemp, minW);
			}
		}
	}
	return false;
}

vector<string> knapsackOpts(const map<string, int>& items, int limit){
	int minW = limit;
	for(auto i : items){
		if(i.second < minW){
			minW = i.second - 1;
		}
	}

	vector<string> curr;
	knapsackHelper(items, limit, curr, minW);
	cout << "Solution: " << endl;
	for (auto c : curr){
		cout << c << endl;
	}
	return curr;
}

int main()
{
	map<string, int> values = { {"itemA",5}, {"itemB",3}, {"itemC",2} };
	knapsackOpts(values, 8);
	
	// Students:  Hand-trace what would output and in what order for
	//            if the map and call above was replaced with the map 
	//            and call below
	// map<string, int> values = { {"itemA",5}, {"itemB",2}, {"itemC",2} };
	// knapsackOpts(values, 6);
	return 0;
}
