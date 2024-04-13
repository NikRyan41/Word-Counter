#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <time.h>
#include <vector>
#include <tuple>
#include<algorithm>

using namespace std;


int main() {
	clock_t start = clock();
	setlocale(LC_ALL, "Russian");
	string tmp = "";
	string pripinaniya="";
	ifstream fin;
	fin.open("Test.txt");
	unordered_map <string, int> machine;
	while (fin >> tmp) {
		for (int i = 0; i < 3; ++i) {
			if (*tmp.begin() == '"' and tmp.size()>=2) {
				pripinaniya = *tmp.begin();
				tmp.erase(tmp.begin(), tmp.begin() + 1);
				++machine[pripinaniya];
			}
			if (tmp.size() > 3 and *(tmp.end() - 1) == '.' and *(tmp.end() - 2) == '.' and *(tmp.end() - 3) == '.') {
				pripinaniya = *(tmp.end() - 1) + *(tmp.end() - 2) + *(tmp.end() - 3);
				tmp.erase(tmp.end() - 3, tmp.end());
				++machine[pripinaniya];
			}
			if (tmp.size() >= 2 and(*(tmp.end() - 1) == ',' or *(tmp.end() - 1) == '.' or *(tmp.end() - 1) == '!' or *(tmp.end() - 1) == ':' or *(tmp.end() - 1) == '?' or *(tmp.end() - 1) == ';')) {
				pripinaniya = *(tmp.end() - 1);
				tmp.erase(tmp.end() - 1, tmp.end());
				++machine[pripinaniya];
			}
			if (tmp.size() >= 2 and *(tmp.end() - 1) == ')') {
				pripinaniya = *(tmp.end() - 1);
				tmp.erase(tmp.end() - 1, tmp.end());
				++machine[pripinaniya];
			}
		}
		++machine[tmp];
	}
	
	vector<tuple<string, int>> result(machine.begin(), machine.end());
	sort(result.begin(), result.end(), [](const auto& p1, const auto& p2) {
		if (get<1>(p1) == get<1>(p2))
			return get<0>(p1) < get<0>(p2);
		else
			return get<1>(p2) < get<1>(p1);

	});



	for (auto i : result) {
		cout << get<1>(i) << "  -  " << get<0>(i) << endl;
	}

	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	cout << seconds;
}
