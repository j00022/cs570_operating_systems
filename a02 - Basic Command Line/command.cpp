#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "command.h"

using namespace std;

//Pushes a command onto the list of command lines and returns the list
list<list<string> > add_commands(list<list<string> > fillMe, list<string> pushMe) {
    fillMe.push_back(pushMe);
    return fillMe;
}

//Launches program
void launch(list<string> program) {
    pid_t pid;
    int n = program.size();
    const char* argv[n];
    int i = 0; //Used to iterate through argv
    //Create and fill argv with commands
	list<string>::iterator itr;
	for (itr = program.begin(); itr != program.end(); itr++) {
		string &k = *itr;
        argv[i++] = (k.c_str());
    }
    argv[n] = '\0';
    
    //Forks program
    if ((pid = fork()) == -1) {
        cout << "Unable to spawn program" << endl;
        return;
    }
    //0 is returned to child if fork success
    //The following are for the child
    else if (pid == 0) {
        //Executes program
        if (execvp(argv[0], (char* const*)argv) == -1){
            cout << "Unable to execute " << program.front() << endl;
            exit(1); //Terminate child
        } 
    }
    //Parent's pid != 0, so it goes here to wait
    else
        pid = wait(NULL);
    if (pid == -1)
        cout << "Process exited with error" << endl;
    else
        cout << "Process exited successfully" << endl;
}

void execute_commands(list<list<string> > commands) {
    //Bool ensures error messages print once each per input
    //Criteria numbering based on assignment 02's bullets
    bool criteria_one_error_printed = false;
    bool criteria_two_error_printed = false;
    bool criteria_three_error_printed = false;

    list<list<string> >::iterator itr;
    //Begin iterating through each command
    for (itr = commands.begin(); itr != commands.end(); itr++) {
        list<string>::iterator itr2;
        list<string> &line = *itr;
        
        //Handles 'cd' command: If only one token after 'cd'
        //attempt to perform, else error
        if (line.front() == "cd") {
            if (line.size() != 2) {
                cout << "Accepts exactly one argument" << endl;
                criteria_two_error_printed = true;
            }
            else {
                string cstr = line.back();
                if (chdir(cstr.c_str()) == -1)
                    cout << "Directory does not exist or is not accessible" << endl;
            }
        }
        //Handles 'pwd' command: Must be a single token command
        else if (line.front() == "pwd" && line.size() == 1) {
            string path = getcwd(NULL, 0);
            if (&path)
                cout << path << endl;
            else 
                cout << "Unable to obtain current directory" << endl;
        }
        
        //Begin iterating through each token of each command line
        else {
            for (itr2 = line.begin(); itr2 != line.end(); itr2++) {
                string &token = *itr2;
                //Handles the following unimplemented tokens: < > &
                if ( token == "<" || token == ">" || token == "&") {
                    itr = commands.erase(itr);
                    itr--;
                    if (!criteria_one_error_printed) {
                        cout << "IO redirection and background not implemented" << endl;
                        criteria_one_error_printed = true;
                    }
                    break;
                }
            } //end of itr2
            //None of the above. Assumes command is a program to be launched
            launch(line);
        }
    } //end of itr
}

void separate_commands(list<list<char> > line) {
    //List of all commands from the input
    list<list<string> > all_commands;
    //A single command, separated by ';' or '|'
    list<string> command;
    
    //Criteria numbering based on assignment 02's bullets
    bool criteria_five_error_printed = false;

    if (line.empty()) {
        return;
    }
    list<list<char> >::iterator itr;
    //Iterates through the list of tokens which are lists of chars
    for (itr = line.begin(); itr != line.end(); itr++) {
        list<char>& t = *itr;
        //Convert char pointer to string
        string s(t.begin(), t.end());
        if (s == ";" || s == "|") {
            if (s == "|") {
                cout << "Pipe not implemented" << endl;
                criteria_five_error_printed = true;
            }
            //A complete command is added to list of all commands
            if (!command.empty())
                all_commands = add_commands(all_commands, command);
                command.clear();
        }
        //Completing the command
        else command.push_back(s);
    }
    if (!command.empty())
        all_commands = add_commands(all_commands, command);   
    execute_commands(all_commands);
}
