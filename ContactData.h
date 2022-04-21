//
// Created by User on 11.04.2022.
//

#ifndef TASK2_CONTACTDATA_H
#define TASK2_CONTACTDATA_H


#include "Contact.h"
#include <vector>
#include <string>

using namespace std;

class ContactData : public Contact {
private:
    vector<ContactData * > linked;
    string device_name;
    //Device *device;

public:
    explicit ContactData(Device *device, int x=0, int y=0, int contact_num=0, int plate_num=0, const string& name="def");
    void link(ContactData *second); //связывание 2 контактов
    void unlink(ContactData *second); //удаление связи 2 контактов
    int isLinked(ContactData *contactData); //Выводит позицию номера контакта contactData в векторе linked
                                            // экземпляра класса, либо -1, если элемент не найден
    string getDeviceName(); //Доступ к имени устройства
    vector<ContactData *> getLinked();

};


#endif //TASK2_CONTACTDATA_H
