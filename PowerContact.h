//
// Created by User on 11.04.2022.
//

#ifndef TASK2_POWERCONTACT_H
#define TASK2_POWERCONTACT_H


#include "Contact.h"

class PowerContact : Contact{
private:
    double power;
public:
    explicit PowerContact(int x=0, int y=0, int contact_num=0, int plate_num=0, double power=0);
    double getPower();
};


#endif //TASK2_POWERCONTACT_H
