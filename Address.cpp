#include "Address.h"

string Address::toString() {
    return this->ip + ":" + this->port;
}