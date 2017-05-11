#include "headers/Command.hh"
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

void Command::execute () {
    
}

// sets userInput to input
void Command::setInput(string input) {
    userInput = input;
}

// separates string by spaces and places each string block into a vector and char * array
void Command::parse() {
    
    if (userInput.size() < 1) {
        return;
    }
    
    unsigned int itrArr = 0;
    
    size_t begin = userInput.find_first_not_of(" ");
    size_t end = userInput.find_last_not_of(" ");
    size_t size = end - begin + 1;
    
    userInput = userInput.substr(begin, size);
    
    char * cstrUserInput = new char [userInput.length() + 1];
    strcpy(cstrUserInput, userInput.c_str());
    char * token = strtok(cstrUserInput, " ");
    
    while (token != NULL) {
        arguments.push_back(token);
        argArr[itrArr] = token;
        token = strtok(NULL,  " ");
        itrArr++;
    }
    return;
}

// outputs userInput
void Command::printInput() {
    cout << "Command::printInput(): " << userInput << endl;
}

// outputs arguments vector
void Command::printArgs() {
    for (unsigned int i = 0; i < arguments.size(); i++) {
        cout << "Command::printArgs(): " << arguments.at(i) << endl;
    }
    return;
}

// returns userInput
string Command::getInput() {
    return userInput;
}

// returns arguments vector
vector<string> Command::getArgs() {
    return arguments;
}

// returns char * array
char ** Command::getArr() {
    return argArr;
}

// sets pass to true
void Command::passed() {
    pass = true;
    return;
}

// sets pass to false
void Command::failed() {
    pass = false;
    return;
}

// returns pass
bool Command::getPass() {
    return pass;
}
