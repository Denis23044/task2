//
// Created by User on 11.04.2022.
//

#include "Contact.h"

Contact::Contact(int x, int y, int contact_num, int plate_num, Device *device) {
    this->x=x;
    this->y=y;
    this->plate_num=plate_num;
    this->contact_num=contact_num;
    this->device=device;
}

int Contact::getX() {
    return this->x;
}
int Contact::getY() {
    return this->y;
}

int Contact::getContactNum() {
    return this->contact_num;
}

int Contact::getPlateNum() {
    return this->plate_num;
}

Device *Contact::getDevice() {
    return this->device;
}
