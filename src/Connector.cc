#include "headers/Connector.hh"
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

void Connector::execute() {
    
}

void Connector::setType(string input) {
    Type = input;
    return;
}

string Connector::getType() {
    return Type;
}

void Connector::printInput() {
    cout << "Connector::printInput(): " << Type << endl;
}