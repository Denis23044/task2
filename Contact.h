//
// Created by User on 11.04.2022.
//

#ifndef TASK2_CONTACT_H
#define TASK2_CONTACT_H


#include "Device.h"

class Contact {
protected:
    int x;
    int y;
    int contact_num;
    int plate_num;
    Device *device;
public:
    explicit Contact(int x=0, int y=0, int contact_num=0, int plate_num=0, Device *device=nullptr);
    int getX();
    int getY();
    int getContactNum();
    int getPlateNum();
    Device *getDevice();
};


#endif //TASK2_CONTACT_H
