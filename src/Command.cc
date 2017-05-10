#include "headers/Command.hh"
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

void Command::execute () {
    
}

void Command::setInput(string input) {
    userInput = input;
}

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

void Command::printInput() {
    cout << "Command::printInput(): " << userInput << endl;
}

void Command::printArgs() {
    for (unsigned int i = 0; i < arguments.size(); i++) {
        cout << "Command::printArgs(): " << arguments.at(i) << endl;
    }
    return;
}

string Command::getInput() {
    return userInput;
}

vector<string> Command::getArgs() {
    return arguments;
}

char ** Command::getArr() {
    return argArr;
}

void Command::passed() {
    pass = true;
    return;
}

void Command::failed() {
    pass = false;
    return;
}

bool Command::getPass() {
    return pass;
}