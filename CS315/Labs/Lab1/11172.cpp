#include <string>
#include <iostream>

using namespace std;

int main() {
	int userinput;
	cin >> userinput;
	if (!((userinput>0)&&(userinput<15))) {
		return 1;
	}
	cin.ignore();
	for (int i=0; i<userinput; i++) {
		string inputline;
		getline(cin, inputline);
		int split = inputline.find(' ',0);
		string firstNumber = inputline.substr(0, split);
		string secondNumber = inputline.substr(split, inputline.length());
		int firstNumberInt = stoi(firstNumber);
		int secondNumberInt = stoi(secondNumber);
			if (firstNumberInt < secondNumberInt) cout << "<" << endl;
			else if (firstNumberInt > secondNumberInt) cout << ">" << endl;
			else cout << "=" << endl;
	}
}
		
		

