#include <iostream>
#include <readline/readline.h>
#include <list>
#include "tokenizer.h"

using namespace std;

//List of lists of characters
list<list<char> > tokens;
list<char> tok;

/* PRINT TOKENS NOT NEEDED FOR a02
void printTokens() {
    if (tokens.empty()) {
            return;
        }
    cout << '[';
    list<list<char> >::iterator itr;
	//Outer loop, iterates through the list of lists
    for (itr = tokens.begin(); itr != tokens.end(); itr++) {
        list<char>::iterator it;
        list<char>& t = *itr;
        if (itr != tokens.begin()) {
            cout << ',';
        }
        cout << '{';
		//Inner loop, iterates through each list of char
        for (it = t.begin(); it != t.end(); it++) {
            cout << *it;
        } 
        cout << "}";
    }
    cout << ']' << endl;
}
*/

//Only checks for char that results in a new token
bool tokenCheck(char c) {
    list<char> tmp1;
    list<char> tmp2;
    if (c == '|' || c == ';' || c == '<' || c == '>' || c == '&') {
		//Do not want to push_back an empty list
        if (!tok.empty()) {
            tmp1 = tok;
            tokens.push_back(tmp1);
            tok.clear();
        }
        tmp2.push_back(c);
        tokens.push_back(tmp2);
        return false;
    }
    if (isspace(c)) {
        if (!tok.empty()) {
            tmp1 = tok;
            tokens.push_back(tmp1);
            tok.clear();
        }
        return false;
    }
    return true;
}

int quoteHandler(char* input, int j, int size, char quotes) {
    list <char> temp;
	//If the quote is at the end
    if (j == size) {
        return j;
    }
    j++;
	//Quoted text can only be terminated by the same type of quote
    while (input[j] != quotes) {
		//Escape char does not work inside single quotes
        if (quotes == '\"' && j < size - 2 && input[j] == '\\') {
            j++;
        }
        temp.push_back(input[j]);
        if (j == size) {
            tok.splice(tok.end(), temp);
            return j;
        }
        j++;
    }
    tok.splice(tok.end(), temp);
    return j + 1;
}

void tokenizer (int argc, char* argv[]) {
    int size;
    char* input;
    
    tokens.clear();
    tok.clear();
      
    while (input = readline("> ")) {
        size = strlen(input);

    	//Begin tokenizing
        for (int i = 0; i < size; i++) {
			//Single quotes
            if (input[i] == '\'') {
                i = quoteHandler(input, i, size, '\'');
            }
			//Double quotes
            if (input[i] == '\"') {
                i = quoteHandler(input, i, size, '\"');
            }
			//Escape char
            if (input[i] == '\\') {
                i++;
                if (i == size) {
                    input[i] = ' ';
                }    
                tok.push_back(input[i]);
            }
			//Delims
            else if (tokenCheck(input[i])) {
                tok.push_back(input[i]);
            }
        }
        if (!tok.empty()) {
            tokens.push_back(tok);
        }
        break;
    }        
}
