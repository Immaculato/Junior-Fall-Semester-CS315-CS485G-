#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <fcntl.h>

using namespace std;

const string keywords[7] = {"set", "defprompt", "cd", "listprocs", "done", "run", "assignto"};
bool done = false;

struct myword {
	string token;
	string type;
	string usage;
};

string scanner(string word) {
	//for each keyword, see if there is a match.
	for (int i=0; i<7; i++) {
		if (word == keywords[i]) return "keyword";
	}
	//its a string if it starts with a quote.
	if (word[0] == '"') return "string";
	else if (word[0] == '$') return "variable";
	else if (word == "&" || word == "%") return "metaChar";
	else return "word";
}

vector<myword> parsecommand(stringstream& stream) {
	vector<myword> parsedcommand;
	string currtoken;
	//mark token and type for each word by using scanner. additionally, if a string has spaces, figure that out too.
	while (stream >> currtoken) {
		myword currword;
		currword.token = currtoken;
		currword.type = scanner(currtoken);
		if (currword.type == "string" && currtoken[currtoken.length()-1] != '"') {
			bool foundendquote = false;
			while (!foundendquote) {
				string nextpart;
				if (stream >> nextpart) {
					//limitation: strings with separated words with more than 1 spaced are reduced to one space between each
					currtoken+=" "+nextpart;
					if (nextpart[nextpart.length()-1] == '"') {
						foundendquote = true;
					}
				} else {
					//this happens if quotes are opened, but are not closed. may need to handle something specifc here
					foundendquote = true;
				}
			}
			currword.token = currtoken;
		}
		if (currword.type == "variable") {
			currword.token = currtoken.substr(1, currtoken.length()-1);
		} else if (currword.type == "string") {
			currword.token = currtoken.substr(1, currtoken.length()-2);
		} else {
			currword.token = currtoken;
		}
		parsedcommand.push_back(currword);
	}

	//mark the usage of the command (if it has one), then continue.
	if (parsedcommand[0].type == "keyword") {
		for (int j=0; j<7; j++) {
			if (parsedcommand[0].token == keywords[j]) parsedcommand[0].usage=keywords[j];
		}
	} else if (parsedcommand[0].token == "%") {
		for (int i=0; i<parsedcommand.size(); i++) {
			parsedcommand[i].usage="comment";
		}
	} else {
		cout << "unrecognized command" << endl;
		done = true;
	}
	
	//for the remaining words in the line, mark their usages according to the command.		
	if (parsedcommand[0].usage == "set") {
		for (int i=1; i<parsedcommand.size(); i++) {
			if (i==1) parsedcommand[1].usage = "variable";
			else if (i==2) parsedcommand[2].usage = "variableDef";
			else parsedcommand[i].usage = "unused";
		}
	} else if (parsedcommand[0].usage == "defprompt") {
		for (int i=1; i<parsedcommand.size(); i++) {
			if (i==1) parsedcommand[1].usage = "arg";
			else parsedcommand[i].usage = "unused";
		}
	} else if (parsedcommand[0].usage == "cd") {
		for (int i=1; i<parsedcommand.size(); i++) {
			if (i==1) parsedcommand[1].usage = "directoryName";
			else parsedcommand[i].usage = "unused";
		}
	} else if (parsedcommand[0].usage == "listprocs") {
		for (int i=1; i<parsedcommand.size(); i++) {
			parsedcommand[i].usage = "unused";
		}
	} else if (parsedcommand[0].usage == "done") {
		for (int i=1; i<parsedcommand.size(); i++) {
			parsedcommand[1].usage = "unused";
		}
	} else if (parsedcommand[0].usage == "run") {
		for (int i=1; i<parsedcommand.size(); i++) {
			if (i==1) parsedcommand[1].usage = "cmd";
			//to_string requires c++11
			else parsedcommand[i].usage = "parameter "+to_string(i-1);
		}
	} else if (parsedcommand[0].usage == "assignto") {
		for (int i=1; i<parsedcommand.size(); i++) {
			if (i==1) parsedcommand[1].usage = "variable";
			else if (i==2) parsedcommand[2].usage = "cmd";
			else parsedcommand[i].usage = "parameter "+to_string(i-2);
		}
	}
	return parsedcommand;
		
}
		
void executecommand(vector<myword> &parsedcommand, map<string, string> &variablemap, list<string> &processlist, string prompt);

int main() {
	string prompt = "sish > ";
	map<string, string> variablemap;
	list<string> processlist;
	while (!done) {
		cout << prompt;
		string line;
		getline(cin, line);
		stringstream stream(line);
		vector<myword> parsedcommand = parsecommand(stream);
		for (int i=0; i<parsedcommand.size(); i++) {
			cout << "Token type: " << parsedcommand[i].type << " Token: " << parsedcommand[i].token << " Usage: " << parsedcommand[i].usage << endl;
		}
		executecommand(parsedcommand, variablemap, processlist, prompt);
	}
}

void executecommand(vector<myword> &parsedcommand, map<string, string> &variablemap, list<string> &processlist, string prompt) {
		//comment case
		if (parsedcommand[0].usage == "comment") {
			//do nothing i guess
		} else if (parsedcommand[0].usage == "set") {
			variablemap.emplace(parsedcommand[1].token, parsedcommand[2].token);
			for(map<string, string>::iterator it= variablemap.begin(); it != variablemap.end(); it++) {
				cout << "Key: " << it->first<<endl;
			}
			//do something special if variable is PATH setenv()
		} else if (parsedcommand[0].usage == "defprompt") {
			prompt = parsedcommand[1].token;
		} else if (parsedcommand[0].usage == "cd") {
			chdir(parsedcommand[1].token.c_str());
		} else if (parsedcommand[0].usage == "listprocs") {
			for (list<string>::iterator it=processlist.begin(); it!=processlist.end(); ++it) {
    				cout << *it << endl;
			}
		} else if (parsedcommand[0].usage == "done") {
			done = true;
		} else if (parsedcommand[0].usage == "run") {
			//char* command = parsedcommand[1].token.c_str();
			const char* command = parsedcommand[1].token.c_str();
			char* args[parsedcommand.size()-2];
			for (int i=0; i<parsedcommand.size()-2; i++) {
				args[i] = (char*) malloc(256);
			}
			args[parsedcommand.size()-1]=NULL;
			bool timetofork = false;
			for (int i=1; i<parsedcommand.size(); i++) {
				if (parsedcommand[i].token == "&") {
					args[i-1] = NULL;
					timetofork = true;
				} else {
					strncpy(args[i-1], parsedcommand[i].token.c_str(), sizeof(args[i-1]));
				}
			}
			//char* const argv[]= args;
			if (timetofork) {
				pid_t pid;
				pid = fork();
				if (pid == 0) {
					processlist.push_back(command);
					execvp(command, args);
					processlist.remove(command);
					exit(0);
				}
			
			} else {
				int retval, child_status;
				pid_t pid;
				pid = fork();
				if (pid == 0) {
					execvp(command, args);
					exit(0);
				} else {
					retval = wait(&child_status);
				}
			}
		} else if (parsedcommand[0].usage == "assignto") {
			const char* command = parsedcommand[2].token.c_str();
			char* args[parsedcommand.size()-2];
			for (int i=0; i<parsedcommand.size()-2; i++) {
				args[i] = (char*) malloc(256);
			}
			
			args[parsedcommand.size()-1]=NULL;
			for (int i=3; i<parsedcommand.size(); i++) {
				strncpy(args[i-1], parsedcommand[i].token.c_str(), sizeof(args[i-1]));
			}
			//char* const *argv= args;
			int retval, child_status;
			pid_t pid;
			pid = fork();
			if (pid == 0) {
				close(1);
				int fd = open("foo", O_RDWR|O_CREAT, 0777);
				execvp(command, args);
			} else {
				retval = wait(&child_status);
				ifstream myfile("foo");
  				if (myfile.is_open())
  				{
					string line;
					string filecontents = "";
 					while (getline(myfile,line)) {
						filecontents+=line;
					}
					cout << "file contents: " << filecontents << endl;
					string uglystring = "set "+parsedcommand[1].token +" \""+filecontents+"\"";
					stringstream uglystringstream(uglystring);
					vector<myword> newsetvector = parsecommand(uglystringstream);
					executecommand(newsetvector, variablemap, processlist, prompt); 
				}
				remove("foo");
			}
		}
	
}
		
