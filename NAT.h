#ifndef SIMPLIFIEDNAT_NAT_H
#define SIMPLIFIEDNAT_NAT_H

#include <unordered_map>
#include "Address.h"
#include <fstream>
#include <iostream>

class NAT {
    unordered_map<string, unordered_map<string, Address>> addressMappings;
public:
    unordered_map<string, unordered_map<string, Address>> getAddressMappings() {
        return this->addressMappings;
    }

    void mapAddress(Address, Address);

    string translateAddress(Address);

    void loadAddressMappingsFromFile(string);

    void translateAddressFromFileAndWriteToFile(string, string);
};

#endif //SIMPLIFIEDNAT_NAT_H