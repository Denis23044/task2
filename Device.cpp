//
// Created by User on 12.04.2022.
//

#include "Device.h"

using namespace std;

Device::Device(string name) {
    this->name=name;
    //this->contacts={};
}

string Device::getName() {
    return this->name;
}
