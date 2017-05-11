#include "headers/RShellContainer.hh"
#include "headers/Command.hh"
#include "headers/Connector.hh"
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

void RShellContainer::getInput(string input) {
    userInput = input;
    return;
}

void RShellContainer::addCommand(Command * command) {
    Commands.push_back(command);
    return;
}

void RShellContainer::addConnector(Connector * connect) {
    Connectors.push_back(connect);
    return;
}


// Parse userInput into a commands vector and a connectors vector
void RShellContainer::parse() {
    string tempStr;
    
    if (userInput.length() == 0) {                                              // Empty input string
        return;
    }
    
    char * cstrUserInput = new char [userInput.length() + 1];                   // + 1 for \0 (null character)
    strcpy(cstrUserInput, userInput.c_str());                                   // convert input string to cstring
    
    char * token = strtok(cstrUserInput, ";|&#");
    
    while (token != NULL) {
        addCommand(new Command(token));
        token = strtok(NULL, ";|&#");
    }
    
    unsigned itr = 0;
    bool mult = false;                                                          // determines if there will be two connects in series
    while (itr < userInput.length()) {
        if ((itr + 1) >= userInput.length()) {}
        else if (userInput[itr] == ';' && !mult) {
            addConnector(new Connector(";"));
            mult = true;
        }
        else if (userInput[itr] == '#' && !mult) {
            addConnector(new Connector("#"));
            mult = true;
        }
        else if (userInput[itr] == '|' && userInput[itr + 1] == '|' && !mult) {
            addConnector(new Connector("||"));
            mult = true;
        }
        else if (userInput[itr] == '&' && userInput[itr + 1] == '&' && !mult) {
            addConnector(new Connector("&&"));
            mult = true;
        }
        else if (userInput[itr] != ' ' && userInput[itr] != ';' && 
                 userInput[itr] != '#' && userInput[itr] != '|' && 
                 userInput[itr] != '&') {
            mult = false;
        }
        else {}
        
        itr++;
    }
    
    if ((Commands.size() - Connectors.size()) != 1) {
        perror("Error: Incorrect number of commands to connects.\n");
    }
    
    for (unsigned int i = 0; i < Commands.size(); i++) {
        Commands.at(i)->parse();
    }
    
    return;
}

void RShellContainer::execute() {
    if (Commands.size() == 0) {
        return;
    }
    
    bool cntPass = true;
    
    for (unsigned i = 0; i < Commands.size(); i++) {
        if ((strcmp(Commands.at(i)->getArr()[0], "exit") == 0)) {
            exit(1);
        }
        
        // fork process
        if (cntPass) {
            Commands.at(i)->failed();
            pid_t pid = fork();
            if (pid < 0) {                                                      // fork failed
                perror("Fork() failed.");
            }
            else if (pid == 0) {
                if (execvp((Commands.at(i)->getArr()[0]), Commands.at(i)->getArr()) == -1) {
                    perror("Command Error.");
                    
                }
                exit(0);
            }
            else {
                while(wait(0) != pid);
                Commands.at(i)->passed();
            }
            
        }
        
        // change cntPass depending on whether command passed and connector
        if (Connectors.size() > i) {
            if (Connectors.at(i)->getType() == ";") {
                cntPass = true;
            }
            else if (Connectors.at(i)->getType() == "#") {
                return;
            }
            else if (Connectors.at(i)->getType() == "&&") {
                if (Commands.at(i)->getPass()) {
                    cntPass = true;
                }
                else {
                    cntPass = false;
                }
            }
            else if (Connectors.at(i)->getType() == "&&") {
                if (Commands.at(i)->getPass()) {
                    cntPass = false;
                }
                else {
                    cntPass = true;
                }
            }
        }
    }
}

void RShellContainer::clear() {
    Commands.clear();
    Connectors.clear();
    return;
}

void RShellContainer::printInput() {
    cout << "RShellContainer::PrintInput(): " << userInput << endl;
}

void RShellContainer::printCommandsInput() {
    cout << "RShellContainer::PrintCommandsInput(): " << endl;
    
    if (Commands.size() < 1) {
        return;
    }
    
    for (unsigned int i = 0; i < Commands.size(); i++) {
        Commands.at(i)->printInput();
    }
    return;
}

void RShellContainer::printConnectors() {
    cout << "RShellContainer::PrintConnectors(): " << endl;
    
    if (Connectors.size() < 1) {
        return;
    }
    
    for (unsigned int i = 0; i < Connectors.size(); i++) {
        Connectors.at(i)->printInput();
    }
}

void RShellContainer::printCommandsArgs() {
    cout << "RShellContainer::PrintCommandsArgs(): " << endl;
    
    if (Commands.size() < 1) {
        return;
    }
    
    for (unsigned int i = 0; i < Commands.size(); i++) {
        Commands.at(i)->printArgs();
    }
    return;
}
