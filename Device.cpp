//
// Created by User on 12.04.2022.
//

#include "Device.h"

using namespace std;
Device::Device(string name) {
    this->name=name;
    this->setCont=false;
    this->setPower=false;
}
string Device::getName() {
    return this->name;
}

int Device::setContacts(vector<ContactData *> contacts) {
    if(setCont){
        printf("You can't change the set of contacts\n");
        return -1;
    }
    if(contacts.empty()){
        printf("Empty set of contacts\n");
        return -2;
    }
    this->contacts=contacts;
    setCont=true;
    return 0;
}

int Device::setPowerContacts(vector<PowerContact *> power_contacts) {
    if(setPower){
        printf("You can't change the set of power_contacts\n");
        return -1;
    }
    if(power_contacts.empty()){
        printf("Empty set of power_contacts\n");
        return -2;
    }
    this->power_contacts=power_contacts;
    setPower=true;
    return 0;
}

vector<ContactData *> Device::getContacts() {
    return this->contacts;
}

vector<PowerContact *> Device::getPowerContacts() {
    return this->power_contacts;
}


