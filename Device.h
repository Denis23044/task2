//
// Created by User on 12.04.2022.
//

#ifndef TASK2_DEVICE_H
#define TASK2_DEVICE_H
#include <string>
#include <vector>
#include <tuple>
//#include "Contact.h"

using namespace std;
class ContactData;
class PowerContact;

class Device {
private:
    string name;
    bool setCont; //Хочу сделать так, чтобы можно было множество контактов присвоить лишь однажды.
                  //Изменить его потом вот так просто будет уже нельзя, как и на физическом устройстве.
    bool setPower;
    vector<ContactData *> contacts;
    vector<PowerContact *> power_contacts;
public:
    explicit Device(string name="default");
    string getName();
    vector<ContactData *> getContacts();
    vector<PowerContact*> getPowerContacts();
    int setContacts(vector<ContactData *> contacts); //Вернет 0, если все ок
    int setPowerContacts(vector<PowerContact *> power_contacts); //Вернет 0, если все ок
};


#endif //TASK2_DEVICE_H
