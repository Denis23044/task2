//
// Created by User on 12.04.2022.
//

#ifndef TASK2_DEVICE_H
#define TASK2_DEVICE_H

#include <string>
#include "Contact.h"
#include <vector>

using namespace std;

class Device {
private:
    string name;
    //vector<Contact *> contacts;
public:
    explicit Device(string name="default");
    string getName();
};


#endif //TASK2_DEVICE_H
