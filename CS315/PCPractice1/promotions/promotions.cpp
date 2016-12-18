#include <iostream>

using namespace std;

int main() {
	int begininternal, endinterval, numemployees, relations;
	int certainpromotions, impossiblepromotions;
	cin >> begininterval;
	cin >> endinterval;
	cin >> numemployees;
	cin >> relations;
	int superiors[numemployees];
	//read in superiors for each employee
	for (int i=0; i<relations; i++) {
		int num1, num2;
		cin >> num1;
		cin >> num2;
		superiors[num2]+=1;
	}
	//find max superiors for any employee
	int maxsuperiors=-1;
	for (int i=0; i < numemployees; i++) {
		if (superiors[i] > maxsuperiors) maxsuperiors = superiors[i];
	}
	
	//process it
	int promotions = endinterval;
	bool answerfound = false;
	//while we arent done,
	while (!answerfound) {
		//find the amount of people at the current level.
		int currlevelsuperiors=0;
		int currlevel=0;
		//for each employee,
		for (int j=0; j<numemployees; j++) {
			//if they are at the desired level, tally them.
			if (superiors[j] == currlevel) currlevelsuperiors+=1;
		}
		//if we have enough promotions left to fit this level,
		if (promotions >= currlevelsuperiors) {
			//keep going with 
			promotions-=currlevelsuperiors;
			certainpromotions+=currlevelsuperiors;
		} else {
			impossiblepromotions = employees - promotions;
		}
	}
}
			
