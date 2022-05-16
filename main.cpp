#include <iostream>
#include <cassert>
#include "Contact.h"
#include "ContactData.h"
#include "PowerContact.h"
#include "Plate.h"

using namespace std;
int main() {
    Device device=Device("The Rolling Stones");
    Device device2=Device("David Bowie");
    ContactData cd1 = ContactData(&device, 1,2,1,2,"laugh? I nearly died");
    ContactData cd2 = ContactData(&device, 2,2,2,2,"Angie");
    ContactData cd3 = ContactData(&device2, 23,26,3,2,"The man who sold the world");
    ContactData cd4 = ContactData(&device2, 23,27,4,2,"Space oddity");
    PowerContact pc1= PowerContact(&device, 20, 7, 5, 2, 30);
    PowerContact pc2= PowerContact(&device2, 6, 21, 6, 1, 25);
    PowerContact pc3= PowerContact(&device2, 6, 21, 6, 2, 27);

    //Привязываю контакты к устройствам
    vector<ContactData *> v1={&cd1, &cd2};
    vector<ContactData *> v2={&cd3, &cd4};
    vector<PowerContact *> v3={&pc1};
    vector<PowerContact *> v4={&pc2};
    device.setContacts(v1);
    device2.setContacts(v2);
    device.setPowerContacts(v3);
    device2.setPowerContacts(v4);

    assert(!device.getContacts().empty());
    assert(!device2.getContacts().empty());
    assert(!device.getPowerContacts().empty());
    assert(!device2.getPowerContacts().empty());

    //Проверяю невозможность изменения контактов
    printf("Check if I can change the set of contacts\n");
    device.setContacts(v2);
    printf("\n");

    //Проверяю связывание
    cd1.link(&cd3);
    cd2.link(&cd4);

    assert(cd1.isLinked(&cd3) >=0);
    assert(cd2.isLinked(&cd4) >=0);

    cd1.link(nullptr);
    cd1.link(&cd2);

    cd1.link(&cd2);
    assert(cd1.isLinked(&cd2)>=0);

    //Проверяю отвязывание
    cd1.unlink(&cd2);
    assert(cd1.isLinked(&cd2)<0);

    cd1.unlink(nullptr);
    cd1.unlink(&cd2);

    //Проверяю доступ к связанным устройствам
    printf("trying to get another device\n");
        //Вообще говоря, поле deviceName в классе ContactData лишнее, т.к. там и так есть ссылка на Device,
        //но удобно оказалось проверять доступ к другому устройству, если сделать имена устройства в контакте
        //и в самом устройстве разными
    cout <<"device2 is   " << (device.getContacts()[0]->getLinked()[0]->getDevice()->getName()) << endl;

    //Проверяем плату
    Plate plate=Plate(0, 29.5, 0, 31.5, 2);
    plate.addContact(&cd1);
    cout << plate.addContact(&cd1) << endl << "Next step\n"; //Должен выдать здесь ошибку, т.к. координаты контактов совпадают
    cout << plate.addContact(&cd2) << endl;
    cout << plate.addContact(&cd3) << endl;
    cout << plate.addContact(&cd4) << endl;
    cout << plate.addContact(&pc1) << endl;
    cout << plate.addContact(&pc3) << endl;
    cout << plate.addContact(&pc2) << endl; //Должен выдать здесь ошибку, т.к. номера плат не совпадают

    cout << "print\n";
    plate.print();

        //Проверка удаления
    plate.removeContact(40, 50); //Не попадает на плату
    plate.removeContact(4, 4); //Нет контакта в этой точке
    plate.removeContact(1, 2); //cd1
    plate.print();
    plate.addContact(&cd1);

        //Проверка поиска элементов
    vector<Contact *> v=plate.findContacts(0, 30, 0, 30); //Вся плата
    cout << endl << "Find Contacts: " << endl;
    for(auto & contact : v){
        contact->print();
    }
    v=plate.findContacts(30, 40, 30, 40); //Не попадает на плату
    cout << endl << "Find Contacts: " << endl;
    for(auto & contact : v){
        contact->print();
    }
    v=plate.findContacts(25, 15, 6, 26.5); //2 контакта в [20, 7] и [23, 26]
    cout << endl << "Find Contacts: " << endl;
    for(auto & contact : v){
        contact->print();
    }
    v=plate.findContacts(23, 23, 27, 27); //Нашелся 1 конкретный контакт
    cout << endl << "Find Contacts: " << endl;
    for(auto & contact : v){
        contact->print();
    }

    cout <<endl;
    cout << "Nearest Neighbour\n";
        //Проверка поиска ближайшего к контакту соседа
    Contact *c=plate.nearestNeighbour(&cd1); //(2,2)
    if(c== nullptr){
        cout << "Wrong!\n";
    }else c->print();

    c=plate.nearestNeighbour(&pc3); // (23,26)
    if(c== nullptr){
        cout << "Wrong!\n";
    }else c->print();

    c=plate.nearestNeighbour(&pc2); //no
    if(c== nullptr){
        cout << "Wrong!\n";
    }else c->print();
    return 0;
}
