#include <iostream>
#include <cassert>
#include "Contact.h"
#include "ContactData.h"

using namespace std;
int main() {
    ContactData cd1 = ContactData(1,2,1,1,"cd1");
    ContactData cd2 = ContactData(2,2,2,1,"cd2");
    ContactData cd3 = ContactData(23,26,3,1,"cd3");
    ContactData cd4 = ContactData(23,27,4,1,"cd4");

    //Проверяю связывание
    cd1.link(&cd2);
    cd3.link(&cd4);

    //printf("isLinked==%d\n", cd1.isLinked(&cd2));
    assert(cd1.isLinked(&cd2) >=0);
    assert(cd3.isLinked(&cd4) >=0);

    cd1.link(NULL);
    cd1.link(&cd2);

    cd1.link(&cd3);
    assert(cd1.isLinked(&cd3)>=0);

    //Проверяю отвязывание
    cd1.unlink(&cd3);
    assert(cd1.isLinked(&cd3)<0);

    cd1.unlink(NULL);
    cd1.unlink(&cd3);

    return 0;
}
