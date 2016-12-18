#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
	int parties, guesses;
	cin >> parties;
	cin >> guesses;
	map<string, int> partymap;
	for (int i=0; i<parties; i++) {
		string party;
		cin >> party;
		float percent;
		cin >> percent;
		percent *= 10;
		//partyvalues[i] = percent;
		partymap.emplace(party, percent);
	}
	bool answers[guesses];
	for (int i=0; i<guesses; i++) {
		string parsedguess[parties*2+1];
		int runningtotal=0;
		bool plusfound = true;
		int j=0;
		while (plusfound) {
			cin >> parsedguess[j];
			cin >> parsedguess[j+1];
			if (parsedguess[j+1] != "+") {
				runningtotal+=partymap[parsedguess[j]];
				plusfound = false;
			} else {
				runningtotal+=partymap[parsedguess[j]];
			}
			j+=2;
		}
		cout << runningtotal << endl;
		int comparisonnumber;
		cin >> comparisonnumber;
		comparisonnumber*=10;
		string comparesymbol;
		comparesymbol = parsedguess[j-1];
		if (comparesymbol == "<") {
			answers[i] = (runningtotal<comparisonnumber);
		}
		else if (comparesymbol == ">") {
			answers[i] = (runningtotal > comparisonnumber);
		}
		else if (comparesymbol == "<=") {
			answers[i] = (runningtotal <= comparisonnumber);
		}
		else if (comparesymbol == ">=") {
			answers[i] = (runningtotal >= comparisonnumber);
		}
		else if (comparesymbol == "=") {
			answers[i] = (runningtotal == comparisonnumber);
		}
	}
	for (int i=0; i<guesses; i++) {
		string answer;
		if (answers[i]) answer = "correct.";
		else answer = "incorrect.";
		cout << "Guess #" << i+1 << " was " << answer << endl;
	}
}
