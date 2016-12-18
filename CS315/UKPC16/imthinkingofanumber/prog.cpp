#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

main() {
	vector<string> answers;
	while (true) {
		int greaterthan=0;
		int lessthan=50001;
		vector<int> divisibleby;
		divisibleby.push_back(1);
		int value;
		cin >> value;
		if (value == 0) break;
		cin.ignore();
		for (int i=0; i<value; i++) {
			string line;
			getline(cin, line);
			stringstream stream(line);
			string keyword;
			stream >> keyword;
			int number;
			if (keyword == "greater") {
				stream >> keyword;
				stream >> number;
				if (number>greaterthan) greaterthan=number;
			} else if (keyword == "less") {
				stream >> keyword;
				stream >> number;
				if (number<lessthan) lessthan=number;
			} else if (keyword == "divisible") {
				stream >> keyword;
				stream >> number;
				divisibleby.push_back(number);
			}
		}
		vector<int> numbers;
		bool doneearly = false;
		if (greaterthan>=lessthan-1) { 
			answers.push_back("none");
			doneearly=true;
		} else if (lessthan == 50001) {
			answers.push_back("infinite");
			doneearly=true;
		}
		bool hasdivisors = divisibleby.size() > 0;
		if (!doneearly) {
			for (int i=greaterthan+1; i<lessthan; i++) {
				if (!hasdivisors) numbers.push_back(i);
				int tally = 0;
				for (int j=0; j<divisibleby.size(); j++) {
					if (i % divisibleby[j] == 0) tally++;
				}
				if (tally == divisibleby.size()) numbers.push_back(i);
			}
			string entry = "";
			for (int i=0; i<numbers.size(); i++) {
				entry+=numbers[i];
				if (i<numbers.size()-1) entry+= " ";
			}
			if (hasdivisors && numbers.size() == 0) {
				answers.push_back("none");
			} else {
				answers.push_back(entry);
			}
		}
	}
	for (int i=0; i<answers.size(); i++) {
		cout << answers[i];
		if (i<answers.size()-1) cout << endl;
	}
}
