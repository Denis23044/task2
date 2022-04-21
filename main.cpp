#include <iostream>
#include <cassert>
#include "Contact.h"
#include "ContactData.h"
#include "PowerContact.h"

using namespace std;
int main() {
    Device device=Device("The Rolling Stones");
    Device device2=Device("David Bowie");
    ContactData cd1 = ContactData(&device, 1,2,1,1,"laugh? I nearly died");
    ContactData cd2 = ContactData(&device, 2,2,2,1,"Angie");
    ContactData cd3 = ContactData(&device2, 23,26,3,1,"The man who sold the world");
    ContactData cd4 = ContactData(&device2, 23,27,4,1,"Space oddity");
    PowerContact pc1= PowerContact(&device, 3, 3, 1, 1, 30);
    PowerContact pc2= PowerContact(&device2, 4, 4, 2, 1, 25);

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

    //printf("isLinked==%d\n", cd1.isLinked(&cd2));
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
    cout <<"device2 is   " << (device.getContacts()[0]->getLinked()[0]->getDevice()->getName()) << endl;

    return 0;
}
