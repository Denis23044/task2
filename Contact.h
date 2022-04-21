//
// Created by User on 11.04.2022.
//

#ifndef TASK2_CONTACT_H
#define TASK2_CONTACT_H


#include "Device.h"

class Contact {
private:
    int x;
    int y;
    int contact_num;
    int plate_num;
    Device *device;
protected:
    int setX(int x);                    //Выводит -1 в случае ошибки и 0, если все хорошо
    int setY(int y);                    //Выводит -1 в случае ошибки и 0, если все хорошо
    int setContactNum(int contact_num); //Выводит -1 в случае ошибки и 0, если все хорошо
    int setPlateNum(int plate_num);     //Выводит -1 в случае ошибки и 0, если все хорошо
    int setDevice(Device* device);      //Выводит -1 в случае ошибки и 0, если все хорошо

public:
    explicit Contact(Device *device= nullptr, int x=0, int y=0, int contact_num=0, int plate_num=0);
    int getX() const;
    int getY() const;
    int getContactNum() const;
    int getPlateNum() const;
    Device* getDevice();

};


#endif //TASK2_CONTACT_H
