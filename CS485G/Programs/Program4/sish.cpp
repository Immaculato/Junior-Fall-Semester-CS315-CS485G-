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
#include <errno.h>

using namespace std;

const int SUCCESS = 0;
const int WRONG_PARAMS = 1;
const int INVALID_STRING = 2;

const string keywords[7] = {"set", "defprompt", "cd", "listprocs", "done", "run", "assignto"};
bool done = false;

bool validString = true;

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

string expressVariables(string token, map<string, string> variablemap) {
        //************* THIS IS THE PART BY KT ************
        string rebuiltString = "";
        string variable = "";
        bool buildingVar = false;
        for (int i=0; i<token.length(); i++ ) {
                if (!buildingVar && token[i] == '$') {
                        buildingVar = true;
                } else if (buildingVar && (i==token.length()-1 || token[i] == ' ' )) {
                        //edge case
                        if (i == token.length()-1) variable+=token[i];

                        if (variablemap.find(variable) != variablemap.end()) rebuiltString+=variablemap[variable];
                        else if (variable == "PATH") rebuiltString+=getenv("PATH");
                        else rebuiltString+="$"+variable;
                        variable = "";
                        buildingVar = false;
                } else if (buildingVar) {
                        variable+=token[i];
                } else {
                        rebuiltString+=token[i];
                }
        }
        return rebuiltString;
}
                                        //*********** END OF KT PART *************



vector<myword> parsecommand(string line) {
        vector<myword> parsedcommand;
        vector<string> builttokens;
        string currtoken = "";
        bool buildingstring = false;
        //mark token and type for each word by using scanner. additionally, if a string has spaces, figure that out too.
        for (int i=0; i<line.length(); i++) {
                //if we know we are building a string and we encounter a quote, we're done with that string.
                if (buildingstring && line[i] == '"') {
                        buildingstring = false;
                        currtoken+=line[i];
                        builttokens.push_back(currtoken);//add it to vector of pared tokens
                        currtoken = "";
                //if we aren't building a string and encounter a quote, now we are.
                } else if (line[i] == '"') {
                        currtoken+=line[i];
                        buildingstring = true;
                //if we encounter a space but we are building a string, add it in the string.
                } else if (i==line.length()-1) {
                        if(buildingstring){
                                validString = false;
                        }
                        currtoken+=line[i];
                        builttokens.push_back(currtoken);
                } else if (line[i] == ' ' && buildingstring) {
                        currtoken+=line[i];
                //if we encounter a space but we aren't building a string, add the token to the list.
                } else if (line[i] == ' ') {
                        if (!(currtoken=="")) builttokens.push_back(currtoken);//add it to vector of parsed tokens
                        currtoken = "";
                } else {
                        currtoken+=line[i];
                }
        }
        //for each token we just built above, make some minor modifications to the tokens for certain types.
        for (int i=0; i<builttokens.size(); i++) {
                string currtoken = builttokens[i];
                myword currword;
                currword.token = currtoken;
                currword.type = scanner(currtoken);
                if (currword.type == "string") {
                        //limitation: if there isn't a closing quote, this will cut off last quote. we aren't going to run it regardless
                        currword.token = currtoken.substr(1, currtoken.length()-2);
                }
                parsedcommand.push_back(currword);
        }
        if (parsedcommand.size() == 0)
                parsedcommand.push_back(myword{"","",""});
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
                cout << "Unrecognized command." << endl;
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

int executecommand(vector<myword> &parsedcommand, map<string, string> &variablemap, list<string> &processlist, string &prompt);

void printParserInfo(vector<myword> parsedcommand) {
        for (int i=0; i<parsedcommand.size(); i++) {
                cout << "Token type: " << parsedcommand[i].type << " Token: " << parsedcommand[i].token << " Usage: " << parsedcommand[i].usage << endl;
        }
}

int main() {
        int returnCode;
        string prompt = "sish > ";
        map<string, string> variablemap;
        variablemap.emplace("ShowTokens", "0");
        list<string> processlist;
        while (!done) {
                cout << prompt;
                string line;
                getline(cin, line);
                if(line=="")
                        line = "\n";
                validString = true;
                vector<myword> parsedcommand = parsecommand(line);
                if(variablemap["ShowTokens"] == "1"){
                        printParserInfo(parsedcommand);
                }
                if(validString){
                        for (int i=0; i<parsedcommand.size(); i++) {
                                parsedcommand[i].token = expressVariables(parsedcommand[i].token, variablemap);
                        }
                        returnCode = executecommand(parsedcommand, variablemap, processlist, prompt);
                }
                else
                        cout << "Error: Expected closing quote." << endl;

                if(returnCode == WRONG_PARAMS)
                        cout << "Incorrect number of parameters for command." << endl;
        }
}

int executecommand(vector<myword> &parsedcommand, map<string, string> &variablemap, list<string> &processlist, string &prompt) {
                //comment case
                if (parsedcommand[0].usage == "comment") {
                        //do nothing i guess
                } else if (parsedcommand[0].usage == "set") {
                        if(parsedcommand.size() != 3){
                                return WRONG_PARAMS;
                        }
                        if (parsedcommand[1].token == "PATH") setenv("PATH", parsedcommand[2].token.c_str(), 1);
                        else {
                                if (!variablemap.emplace(parsedcommand[1].token, parsedcommand[2].token).second) {
                                        variablemap[parsedcommand[1].token] = parsedcommand[2].token;
                                }

                        }
                } else if (parsedcommand[0].usage == "defprompt") {
                        if(parsedcommand.size() != 2){
                                return WRONG_PARAMS;
                        }
                        prompt = parsedcommand[1].token;
                } else if (parsedcommand[0].usage == "cd") {
                        if(parsedcommand.size() != 2){
                                return WRONG_PARAMS;
                        }
                        int valid = chdir(parsedcommand[1].token.c_str());
                        if(valid != 0)
                                perror(parsedcommand[1].token.c_str());
                } else if (parsedcommand[0].usage == "listprocs") {
                        if(parsedcommand.size() > 1){
                                return WRONG_PARAMS;
                        }
                        for (list<string>::iterator it = processlist.begin(); it != processlist.end(); it++) {
                                cout << *it << endl;
                        }
                } else if (parsedcommand[0].usage == "done") {
                        done = true;
                } else if (parsedcommand[0].usage == "run") {
                        if(parsedcommand.size() < 2){
                                return WRONG_PARAMS;
                        }
                        bool runabsolute = false;
                        if(parsedcommand[1].token[0] == '.' || parsedcommand[1].token[0] == '/' ){
                                runabsolute = true;
                        }
                        //char* command = parsedcommand[1].token.c_str();
                        const char* command = parsedcommand[1].token.c_str();
                        char* args[parsedcommand.size()-1];
                        for (int i=0; i<parsedcommand.size()-1; i++) {
                                args[i] = (char*) malloc(256);
			}
			args[parsedcommand.size()-1] = NULL;
                        bool runinbackground = false;
                        for (int i=1; i<parsedcommand.size(); i++) {
                                if (parsedcommand[i].token == "&") {
                                        args[i-1] = NULL;
                                        runinbackground = true;
                                } else {
                                        strncpy(args[i-1], parsedcommand[i].token.c_str(), parsedcommand[i].token.length() + 1);
                                }
                        }
                        //if running in background
                        string newprocess = parsedcommand[0].token;
                        if (runinbackground) {
                                pid_t pid;
                                pid = fork();
                                processlist.emplace_back(newprocess+" (BACKGROUND)");
                                if (pid == 0) {
                                      //  pid_t pid2 = fork();
                                      //  if(pid2 == 0){
                                                if(runabsolute){
                                                       int valid = execv(command, args);
							if(valid == -1)
								perror((parsedcommand[1].token + " Error").c_str());
							exit(1);
                                                }
                                                else{
                                                       	int valid = execvp(command, args);
							if(valid == -1)
								perror((parsedcommand[1].token + " Error").c_str());
							exit(1);
						}
                                       
                                       // else{
                                       //         int waiting, child_status;
                                       //         waiting = wait(&child_status);
                                       //         exit(0);
                                       // }
                                }

                        } else {
                                int retval, child_status;
                                processlist.emplace_back(newprocess);
                                list<string>::iterator it = processlist.end();
                                it--;
                                pid_t pid;
                                pid = fork();
                                if (pid == 0) {
                                        if(runabsolute){
                                                int valid = execv(command, args);
						if(valid == -1)
							perror((parsedcommand[1].token + " Error").c_str());
						exit(1);
                                                }
                                        else{
                                               	int valid = execvp(command, args);
						if(valid == -1)
							perror((parsedcommand[1].token + " Error").c_str());
						exit(1);
					}
                                               
                                } else {
                                        retval = wait(&child_status);
                                        processlist.erase(it);
                                        processlist.emplace_back(newprocess+" (FINISHED)");

                                }
                        }

			for(int i = 0; i < parsedcommand.size()-1; i++){
                                free(args[i]);
                        }

                } else if (parsedcommand[0].usage == "assignto") {
                        if(parsedcommand.size() < 3){
                                return WRONG_PARAMS;
                        }
                        bool runabsolute = false;
                        if(parsedcommand[2].token[0] == '.' || parsedcommand[2].token[0] == '/' ){
                                runabsolute = true;
                        }
                        const char* command = parsedcommand[2].token.c_str();
                        char* args[parsedcommand.size()-1];
                        for (int i=0; i<parsedcommand.size()-1; i++) {
                                args[i] = (char*) malloc(256);
                        }

                        args[parsedcommand.size()-2]=NULL;
                        for (int i=2; i<parsedcommand.size(); i++) {
                                strncpy(args[i-2], parsedcommand[i].token.c_str(), parsedcommand[i].token.length() + 1);
                        }
                        string newprocess = parsedcommand[1].token;
                        int retval, child_status;
                        processlist.emplace_back(newprocess);
                        list<string>::iterator it = processlist.end();
                        it--;
                        pid_t pid;
                        pid = fork();
                        if (pid == 0) {
                                close(1);
                                int fd = open("/tmp/foo", O_RDWR|O_CREAT, 0777);
                                if(runabsolute){
                                        int valid = execv(command, args);
					if(valid == -1)
						perror((parsedcommand[2].token + " Error").c_str());
					close(fd);
					exit(1);
                                }
                                else{
                                        int validate= execvp(command, args);
					if(validate == -1)
						perror((parsedcommand[2].token + " Error").c_str());
					close(fd);
					exit(1);
				}
                        } else {
                                retval = wait(&child_status);
                                processlist.erase(it);
                                processlist.emplace_back(newprocess+" (FINISHED)");
                                ifstream myfile("/tmp/foo");
				string filecontents = "";
                                if (myfile.is_open())
                                {
                                        string line;
                                        while (getline(myfile,line)) {
                                                filecontents+=line;
                                        }
                                        string uglystring = "set "+parsedcommand[1].token +" \""+filecontents+"\"";
                                        vector<myword> newsetvector = parsecommand(uglystring);
                                        executecommand(newsetvector, variablemap, processlist, prompt);
                                }
				myfile.close();
                                remove("/tmp/foo");
                        }

                        //deallocate memory assigned to args
                        for (int i=0; i<parsedcommand.size()-1; i++) {
                                free(args[i]);
                        }
                }

                return SUCCESS;

}

