#ifndef SIMPLIFIEDNAT_ADDRESS_H
#define SIMPLIFIEDNAT_ADDRESS_H

#include <vector>
#include <string>
#include <sstream>
#include "Utility.h"

using namespace std;

class Address {
public:
    string ip;
    string port;

    Address(string address) {
        // split address at ':'
        vector<string> addressVector = Utility::splitString(address, ':');

        this->ip = addressVector[0];
        this->port = addressVector[1];
    }

    string toString();
};

#endif //SIMPLIFIEDNAT_ADDRESS_H