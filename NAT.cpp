#include "NAT.h"

/*
 * Adds the mapping of original ip address to translated ip address in the NAT data structure
 * */
void NAT::mapAddress(Address original, Address translated) {
    if (this->addressMappings.find(original.ip) != this->addressMappings.end()) {
        // ip already exists, add to existing entry
        unordered_map<string, Address> portMappings = this->addressMappings.at(original.ip);
        if (portMappings.find(original.port) != portMappings.end()) {
            // port already exists
            portMappings.at(original.port) = translated;
        } else {
            // port does not exist
            pair<string, Address> portAddressPair(original.port, translated);
            portMappings.insert(portAddressPair);
        }
        this->addressMappings.at(original.ip) = portMappings;
    } else {
        // ip does not exist, create new ip key and add port - address mapping
        pair<string, Address> portAddressPair(original.port, translated);
        unordered_map<string, Address> portMappings;
        portMappings.insert(portAddressPair);

        pair<string, unordered_map<string, Address>> ipMappingPair(original.ip, portMappings);
        this->addressMappings.insert(ipMappingPair);
    }
}

/*
 * Translates the given ip address to the mapped network address using the NAT data structure
 * */
string NAT::translateAddress(Address address) {
    if (this->addressMappings.find(address.ip) != this->addressMappings.end()) {
        // exact ip present, search for exact port
        unordered_map<string, Address> portMappings = this->addressMappings.at(address.ip);
        if (portMappings.find(address.port) != portMappings.end()) {
            // exact port present, get mapping
            return portMappings.at(address.port).toString();
        } else {
            // search for any port
            if (portMappings.find("*") != portMappings.end()) {
                // exact port present, get mapping
                return portMappings.at("*").toString();
            } else {
                // no NAT match
                return "";
            }
        }
    } else {
        // search for any ip
        if (this->addressMappings.find("*") != this->addressMappings.end()) {
            // search for port
            unordered_map<string, Address> portMappings = this->addressMappings.at("*");
            if (portMappings.find(address.port) != portMappings.end()) {
                // exact port present, get mapping
                return portMappings.at(address.port).toString();
            } else {
                // no NAT match
                return "";
            }

        } else {
            // no NAT match
            return "";
        }
    }
}

/*
 * Loads address mappings from file to NAT data structure
 * */
void NAT::loadAddressMappingsFromFile(string fileName) {
    // read NAT input file
    string line;
    ifstream file(fileName);
    if (file.is_open()) {
        while (getline(file, line)) {
            // cout << line << '\n';
            // split original and translated addresses at ',' and add to the NAT address map
            vector<string> addressesVector = Utility::splitString(line, ',');
            Address original(Utility::trimString(addressesVector[0]));
            Address translated(Utility::trimString(addressesVector[1]));
            this->mapAddress(original, translated);
        }
        file.close();
        cout << "NAT file loaded successfully." << endl;
    } else {
        cout << "Unable to open file." << endl;
    }
}

/*
 * Translates each address from input file to its corresponding network address and writes it to the output file
 * */
void NAT::translateAddressFromFileAndWriteToFile(string inputFileName, string outputFileName) {
    // open OUTPUT file
    ofstream outputFile(outputFileName);
    if (outputFile.is_open()) {
        // read FLOW input file
        string line;
        ifstream inputFile(inputFileName);
        if (inputFile.is_open()) {
            while (getline(inputFile, line)) {
                // cout << line << '\n';
                Address address(Utility::trimString(line));
                string translatedAddress = this->translateAddress(address);
                if (translatedAddress.empty()) {
                    outputFile << "No nat match for " << address.toString() << "\n";
                } else {
                    outputFile << address.toString() << " -> " << translatedAddress << "\n";
                }

            }
            inputFile.close();
            outputFile.close();
            cout << "OUTPUT file generated successfully." << endl;
        } else {
            cout << "Unable to open input file." << endl;
        }
    } else {
        cout << "Unable to open output file." << endl;
    }
}
