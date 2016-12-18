#include <string>
#include <iostream>
#include <sstream>

using namespace std;

bool match (int passstart, int messageindex, string pass, string message) {
	char okforrepeats = pass[passstart];
	for (int i=passstart+1; i<pass.length(); i++) {
		if (okforrepeats != message[messageindex] && pass[i] == message[messageindex]) return true;
	}
	return false;
}

int main (int argc, char** argv ) {
	string line;
	string password;
	string message;
	getline(cin, line);
	stringstream stream(line);
	stream >> password;
	stream >> message;
	int passindex=0;
	int messageindex=0;
	int messagelength = message.length();
	while (messageindex < messagelength) {
		if (match(passindex, messageindex, password, message)) {
			cout << "FAIL";
			return 0;
		} else {
			if (password[passindex] == message[messageindex]) passindex++;
		}
		if (passindex == password.length()) {
			cout << "PASS";
			return 0;
		}
		messageindex++;
	}
	if (passindex != password.length()) cout << "FAIL";
	return 0;
}
