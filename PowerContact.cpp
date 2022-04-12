//
// Created by User on 11.04.2022.
//

#include "PowerContact.h"

double PowerContact::getPower() {
    return this->power;
}

PowerContact::PowerContact(int x, int y, int contact_num, int plate_num, double power) {
    this->x=x;
    this->y=y;
    this->contact_num=contact_num;
    this->plate_num=plate_num;
    this->power=power;
}

