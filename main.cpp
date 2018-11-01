#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "NAT.h"

using namespace std;

int main() {

    NAT nat;
    nat.loadAddressMappingsFromFile("NAT");
    nat.translateAddressFromFileAndWriteToFile("FLOW", "OUTPUT");

    /*for (auto &x: nat.getAddressMappings()) {
        for (auto &y: x.second) {
            cout << x.first << ":" << y.first << ", " << y.second.toString() << endl;
        }
    }
    cout << endl;*/

    return 0;
}