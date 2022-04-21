//
// Created by User on 11.04.2022.
//

#include "PowerContact.h"

double PowerContact::getPower() const {
    return this->power;
}

PowerContact::PowerContact(Device *device, int x, int y, int contact_num, int plate_num, double power) {
    this->setX(x);
    this->setY(y);
    this->setPlateNum(plate_num);
    this->setContactNum(contact_num);
    this->setDevice(device);
    this->power=power;
}

