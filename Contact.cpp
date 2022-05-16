//
// Created by User on 11.04.2022.
//

#include <iostream>
#include "Contact.h"

Contact::Contact(Device *device, int x, int y, int contact_num, int plate_num) {
    this->x=x;
    this->y=y;
    this->plate_num=plate_num;
    this->contact_num=contact_num;
    this->device=device;
}

int Contact::getX() const {
    return this->x;
}
int Contact::getY() const {
    return this->y;
}

int Contact::getContactNum() const {
    return this->contact_num;
}

int Contact::getPlateNum() const {
    return this->plate_num;
}

int Contact::setX(int x) {
    if(x<0){return -1;}
    this->x=x;
    return 0;
}

int Contact::setY(int y) {
    if(y<0){return -1;}
    this->y=y;
    return 0;
}

int Contact::setContactNum(int contact_num) {
    if(contact_num<0){return -1;}
    this->contact_num=contact_num;
    return 0;
}

int Contact::setPlateNum(int plate_num) {
    if(plate_num<0) return -1;
    this->plate_num=plate_num;
    return 0;
}

int Contact::setDevice(Device *device) {
    if(device==nullptr) return -1;
    this->device= device;
    return 0;
}

Device* Contact::getDevice() const{
    return this->device;
}

void Contact::print() {
    cout << "Contact Info:" << endl;
    cout << "\tposition:      [" << this->x << ", " << this->y << "]" << endl;
    cout << "\tContact number: " << this->contact_num << endl;
    cout << "\tDevice Name:    " << this->device->getName() << endl;
}
