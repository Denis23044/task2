//
// Created by User on 11.04.2022.
//

#include <iostream>
#include "ContactData.h"

ContactData::ContactData(Device *device, int x, int y, int contact_num, int plate_num, const string& name) : Contact(device, x, y, contact_num, plate_num) {
    this->setX(x);
    this->setY(y);
    this->setPlateNum(plate_num);
    this->setContactNum(contact_num);
    this->linked={};
    this->device_name=name;
    this->setDevice(device);
}

string ContactData::getDeviceName() {
    return this->device_name;
}

void ContactData::link(ContactData *second) {
    //Вот я не понял, могут ли соединяться контакты с разных плат
    // Проверяю, что указатель не нулевой
    if(second== nullptr){
        cout << "failed link: nullptr" << endl;
        return;
    }

    //Проверяю, что контакты не были и так связаны
    if(this->isLinked(second) >=0){
        cout << "failed link: already linked" << endl;
        return;
    }

    //Связываю
    this->linked.push_back(second);
    //cout << "this->linked==" << this->linked[0] << endl;
    second->linked.push_back(this);
}

void ContactData::unlink(ContactData *second) {
    //Проверяю, что указатель не нулевой
    if(second== nullptr){
        cout << "failed unlink: nullptr" << endl;
        return;
    }

    //Проверяю, что контакты были связаны
    int i = this->isLinked(second);
    if(i<0){
        cout << "failed unlink: contacts wasn't linked" << endl;
        return;
    }

    //Отвязываю
    int j = second->isLinked(this);
    this->linked.erase(this->linked.begin()+i);
    second->linked.erase(second->linked.begin()+j);
}

int ContactData::isLinked(ContactData *contactData) {
    //В переменную s сохраню номер контакта, связь с которым нужно проверить
    int s=contactData->getContactNum();
    //cout << "s==" << s << endl;
    int i;
    for (i=0; i<this->linked.size(); i++) {
        //Проверю, совпали ли номера контактов
        if(this->linked[i]->getContactNum()==s) return i;
    }
    //cout << "\tisLinked: i==" << i << endl;
    return -1;
}

vector<ContactData *> ContactData::getLinked() {
    return this->linked;
}
