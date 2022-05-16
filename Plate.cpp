//
// Created by User on 21.04.2022.
//

#include <iostream>
#include <cmath>
#include "Plate.h"

Plate::Plate(double x1, double x2, double y1, double y2, int plateNumber) {
    //Вот не знаю, как прямо в конструкторе проверить, что нельзя создать квадрант нулевой ширины/длины
    //Лучше в коде это проверять буду
    //Хочу, чтобы x1<x2 и y1<y2
    this->plateNumber=plateNumber;
    if(x1>x2){
        this->x2=x1;
        this->x1=x2;
    }else{
        this->x1=x1;
        this->x2=x2;
    }
    if(y1>y2){
        this->y2=y1;
        this->y1=y2;
    }else{
        this->y1=y1;
        this->y2=y2;
    }
    this->isLeaf=true;
    this->isHead=true;
}

int Plate::addContact(Contact *contact) {
    //Проверяю, что номера плат совпадают
    if(contact->getPlateNum()!=this->plateNumber){
        cout << "Plate::addContact()\tThis is another plate" << endl;
        return -1;
    }
    //Проверяю, что это лист
    if(!this->isLeaf){
        //cout << "Plate::addContact()\tNot a leaf\n";
        if(this->NE->addContact(contact)>=0) return 0;
        if(this->NW->addContact(contact)>=0) return 0;
        if(this->SE->addContact(contact)>=0) return 0;
        if(this->SW->addContact(contact)>=0) return 0;
        return -1;
    }
    int x=contact->getX();
    int y=contact->getY();

    //Проверяю, что контакт попадает на плату
    if(this->x1>x || this->x2<x || y<this->y1 || y>this->y2){
        //cout << "Plate::addContact()	Contact doesn't belong to this plate" <<endl;
        return -2;
    }

    //Проверяю, что нельзя посадить 2 контакта в 1 точку
    for(auto & contact1 : this->contacts){
        if(x == contact1->getX() && y == contact1->getY()){
            cout << "Plate::addContact()\tYou can't add 2 contacts at the same place\n";
            return -3;
        }
    }

    //Если максимальная вместимость не превышена, то добавляю контакт
    if(this->contacts.size()<CAPACITY){
        this->contacts.push_back(contact);
        return 0;
    }

    //Часть с разбиением
    //cout << "Plate::addContact()\tFear the walking recursion" << endl;
    this->subDivide();
    //cout << "Plate::addContact()\tsubDivided" << endl;
    if(this->NE->addContact(contact)>=0) return 0;
    if(this->NW->addContact(contact)>=0) return 0;
    if(this->SE->addContact(contact)>=0) return 0;
    if(this->SW->addContact(contact)>=0) return 0;

    //Если вдруг еще что-то не так
    return -4;
}

int Plate::subDivide() {
    this->isLeaf=false;
    double x[3]; //Соберу массив координат рамок новых плат
    double y[3];
    x[0]=this->x1; x[2]=this->x2;
    y[0]=this->y1; y[2]=this->y2;
    x[1]=x[0]+(x[2]-x[0])/2;
    y[1]=y[0]+(y[2]-y[0])/2;
    //cout << "Plate::subDivide()\tarrays created" << endl;

    //Теперь создаю потомков
    (this->NW)=new Plate(x[0], x[1], y[1], y[2], this->plateNumber);
    this->NW->parent=this;
    this->NW->isHead=false;

    (this->NE)=new Plate(x[1], x[2], y[1], y[2], this->plateNumber);
    this->NE->parent=this;
    this->NE->isHead=false;

    (this->SW)=new Plate(x[0], x[1], y[0], y[1], this->plateNumber);
    this->SW->parent=this;
    this->SW->isHead=false;

    (this->SE)=new Plate(x[1], x[2], y[0], y[1], this->plateNumber);
    this->SE->parent=this;
    this->SE->isHead=false;

    //Теперь надо перенести точки в детей
    for(auto & contact : this->contacts){
        //cout << "Plate::subDivide()\tFear the  walking recursion" << endl;
        this->NW->addContact(contact);
        this->NE->addContact(contact);
        this->SW->addContact(contact);
        this->SE->addContact(contact);
    }
    //cout << "Plate::subDivide()\tcontacts transported" << endl;

    this->contacts.clear();
    this->contacts.shrink_to_fit();
    //cout << "Plate::subDivide()\told array deleted" << endl;
    return 0;
}

vector<Contact *> Plate::findContacts(double x1, double x2, double y1, double y2) {
    if(x1>x2){
        double x=x1;
        x1=x2;
        x2=x;
    }
    if(y1>y2){
        double y=y1;
        y1=y2;
        y2=y;
    }
    if(this->isLeaf){
        vector<Contact*> v;
        for(auto & contact : this->contacts){
            int x=contact->getX();
            int y=contact->getY();
            if(x>=x1 && x<=x2 && y>=y1 && y<=y2){
                v.push_back(contact);
            }
        }
        return v;
    }
    //Часть с рекурсией
    vector<Contact*> v;
    double x3, x4, y3, y4;
    //хочу проверить, есть пересечение квадранта с заданной областью, и запустить рекурсию, если нужно

    //NW
    x3=max(this->NW->x1, x1);
    x4=min(this->NW->x2, x2);
    y3=max(this->NW->y1, y1);
    y4=min(this->NW->y2, y2);
    if(x3<=x4 && y3<=y4){
        //Не понял, как здесь воспользоваться insert() или еще чем-то, так что
        //топорно через push_back и цикл
        vector<Contact*> v1=this->NW->findContacts(x1,x2,y1,y2);
        for(auto & contact : v1){
            v.push_back(contact);
        }
    }

    //NE
    x3=max(this->NE->x1, x1);
    x4=min(this->NE->x2, x2);
    y3=max(this->NE->y1, y1);
    y4=min(this->NE->y2, y2);
    if(x3<=x4 && y3<=y4){
        vector<Contact*> v1=this->NE->findContacts(x1,x2,y1,y2);
        for(auto & contact : v1){
            v.push_back(contact);
        }
    }

    //SW
    x3=max(this->SW->x1, x1);
    x4=min(this->SW->x2, x2);
    y3=max(this->SW->y1, y1);
    y4=min(this->SW->y2, y2);
    if(x3<=x4 && y3<=y4){
        vector<Contact*> v1=this->SW->findContacts(x1,x2,y1,y2);
        for(auto & contact : v1){
            v.push_back(contact);
        }
    }

    //SE
    x3=max(this->SE->x1, x1);
    x4=min(this->SE->x2, x2);
    y3=max(this->SE->y1, y1);
    y4=min(this->SE->y2, y2);
    if(x3<=x4 && y3<=y4){
        vector<Contact*> v1=this->SE->findContacts(x1,x2,y1,y2);
        for(auto & contact : v1){
            v.push_back(contact);
        }
    }
    return v;
}

Contact * Plate::nearestNeighbour(Contact * contact) {
    //Сначала хочу убедиться, что такой контакт на плате есть
    if(this->plateNumber!=contact->getPlateNum()){
        //cout << "Plate::nearestNeighbour():\tContact from another plate" << endl;
        return nullptr;
    }
    vector<Contact *> v= this->findContacts(contact->getX(), contact->getX(), contact->getY(), contact->getY());
    if(v.size()==0){
        //cout << "Plate::nearestNeighbour():\t Can't find this contact on the plate" << endl;
        return nullptr;
    }
    //cout << "Plate::nearestNeighbour():\t Came to getLeaf" << endl;
    Plate *q0=this->getLeaf(contact->getX(), contact->getY());
    //cout << "Plate::nearestNeighbour():\t Came to findNeighbour" << endl;
    Contact *c=q0->findNeighbour(contact);
    //c->print();
    //Проверяю, что контакт на плате не 1
    if(c== nullptr){
        //cout << "It is the only one contact on the plate" << endl;
        return nullptr;
    }

    //cout << "Plate::nearestNeighbour():\t Came to dist" << endl;
    double dist=Plate::distance(c, contact);
    Contact *c2=this->searchNearest(contact, dist);
    if (c== nullptr){
        //searchNearest пытается найти контакт ближе, чем dist, но раз у него не получилось, значит таких нет
        return c;
    }
    return c;
}

void Plate::print() {
    if(this->isLeaf){
        cout << "Leaf:" << endl;
        for(auto & contact : this->contacts){
            cout << "\tcontact in (" << contact->getX() << ", " << contact->getY() << ")" << endl;
        }
        return;
    }
    cout << "Node" << endl;
    cout << "NW: x in [" << this->NW->x1 <<", " << this->NW->x2 << "]; " << "y in [" << this->NW->y1 <<", " <<this->NW->y2 << "]" <<endl <<"\t";
    this->NW->print();

    cout << "NE: x in [" << this->NE->x1 <<", " << this->NE->x2 << "]; " << "y in [" << this->NE->y1 <<", " <<this->NE->y2 << "]" <<endl <<"\t";
    this->NE->print();

    cout << "SW: x in [" << this->SW->x1 <<", " << this->SW->x2 << "]; " << "y in [" << this->SW->y1 <<", " <<this->SW->y2 << "]" <<endl <<"\t";
    this->SW->print();

    cout << "SE: x in [" << this->SE->x1 <<", " << this->SE->x2 << "]; " << "y in [" << this->SE->y1 <<", " <<this->SE->y2 << "]" <<endl <<"\t";
    this->SE->print();
}

int Plate::removeContact(int x, int y) {
    //Проверяю, что контакт попадает на плату
    if(this->x1>x || this->x2<x || y<this->y1 || y>this->y2){
        //cout << "Plate::removeContact()\tContact doesn't belong to this plate" <<endl;
        return -1;
    }

    //Теперь надо проверить, лист ли это. Если лист, то удалить контакт, если нет, — запустить рекурсию
    if(this->isLeaf){
        for(int i=0; i<this->contacts.size(); i++){
            if(this->contacts[i]->getX()==x && this->contacts[i]->getY()==y){
                cout << "Contact deleted: " << endl;
                this->contacts[i]->print();
                this->contacts.erase(this->contacts.begin()+i);
                return 0;
            }
        }
        cout << "Plate::removeContact()\tContact wasn't found in [" << x << ", " << y << "]" << endl;
        return -2;
    }

    //Часть с рекурсией
    if(this->NE->removeContact(x, y)>=0) return 0;
    if(this->NW->removeContact(x, y)>=0) return 0;
    if(this->SE->removeContact(x, y)>=0) return 0;
    if(this->SW->removeContact(x, y)>=0) return 0;

    //Если еще что-то пошло не так
    return -3;
}

Plate *Plate::getLeaf(double x, double y) {
    if(this->isLeaf){
        //cout << "Plate::getLeaf():\t leaf: x in [" << this->x1 << ", " << this->x2 << "]" << ";  y in ["<<this->y1 << ", " << this->y2 << "]"<< endl;
        //cout << "point (" << x << ", " << y << ")" << endl;
        if(this->x1<=x && this->x2>=x && this->y1<=y && this->y2>=y){
            //cout << "Plate::getLeaf():\t returned this" << endl;
            return this;
        }
        return nullptr;
    }
    //cout << "Plate::getLeaf():\t fear the walking recursion" << endl;
    Plate * p;
    //cout << "Plate::getLeaf():\t NW: x in [" << this->NW->x1 << ", " << this->NW->x2 << "]" << ";  y in ["<< this->NW->y1<< ", " << this->NW->y2 << "]"<< endl;
    p=this->NW->getLeaf(x, y);
    if(p!= nullptr){
        //cout << "Plate::getLeaf():\t returned NW" << endl;
        return p;
    }
    //cout << "Plate::getLeaf():\t NE: x in [" << this->NE->x1 << ", " << this->NE->x2 << "]" << ";  y in ["<< this->NE->y1<< ", " << this->NE->y2 << "]"<< endl;
    p=this->NE->getLeaf(x, y);
    if(p!= nullptr) {
        //cout << "Plate::getLeaf():\t returned NE" << endl;
        return p;
    }
    //cout << "Plate::getLeaf():\t SW: x in [" << this->SW->x1 << ", " << this->SW->x2 << "]" << ";  y in ["<< this->SW->y1<< ", " << this->SW->y2 << "]"<< endl;
    p=this->SW->getLeaf(x, y);
    if(p!= nullptr){
        //cout << "Plate::getLeaf():\t returned SW" << endl;
        return p;
    }
    //cout << "Plate::getLeaf():\t SE: x in [" << this->SE->x1 << ", " << this->SE->x2 << "]" << ";  y in ["<< this->SE->y1<< ", " << this->SE->y2 << "]"<< endl;
    p=this->SE->getLeaf(x, y);
    if(p!= nullptr){
        //cout << "Plate::getLeaf():\t returned SE" << endl;
        return p;
    }

    return nullptr;
}

Contact * Plate::findNeighbour(Contact *contact) {
    /*По сути алгоритм так работает, что начинается с листа, а потом нужно проверять уже только соседние квадраты.
     * То есть начинается алгоритм с проверки листа, а потом в каждой итерации проверяется не сам квадрат,
     * а только соседние квадраты.
     */
    Contact *c;
    if(this->isLeaf) {
        //cout << "Plate::findNeighbour():\tLeaf" << endl;
        c = this->checkQuad(contact);
        if (c != nullptr) return c;
    }
    //Если в самом квадрате соседа не нашел, нужно подняться к родителю и обойти других потомков
    //Так можно сделать, если это не голова
    if(!this->isHead) {
        double x=this->parent->NW->x2; //координаты центра квадрата
        double y=this->parent->NW->y1;
        if(this->x2==x && this->y1==y){
            //Изначальный квадрат был NW
            //cout << "Plate::findNeighbour():\tNW" << endl;
            c=this->parent->NE->checkQuad(contact);
            if(c!= nullptr) return c;

            c=this->parent->SW->checkQuad(contact);
            if(c!= nullptr) return c;

            c=this->parent->SE->checkQuad(contact);
            if(c!= nullptr) return c;
        }
        if(this->x1==x && this->y1==y){
            //Изначальный квадрат был NE
            //cout << "Plate::findNeighbour():\tNE" << endl;
            c=this->parent->NW->checkQuad(contact);
            if(c!= nullptr) return c;

            c=this->parent->SW->checkQuad(contact);
            if(c!= nullptr) return c;

            c=this->parent->SE->checkQuad(contact);
            if(c!= nullptr) return c;
        }
        if(this->x2==x && this->y2==y){
            //Изначальный квадрат был SW
            //cout << "Plate::findNeighbour():\tSW" << endl;
            c=this->parent->NE->checkQuad(contact);
            if(c!= nullptr) return c;

            c=this->parent->NW->checkQuad(contact);
            if(c!= nullptr) return c;

            c=this->parent->SE->checkQuad(contact);
            if(c!= nullptr) return c;
        }
        if(this->x1==x && this->y2==y){
            //Изначальный квадрат был SE
            //cout << "Plate::findNeighbour():\tSE" << endl;
            c=this->parent->NE->checkQuad(contact);
            if(c!= nullptr) return c;

            c=this->parent->NW->checkQuad(contact);
            if(c!= nullptr) return c;

            c=this->parent->SW->checkQuad(contact);
            if(c!= nullptr) return c;
        }
        //Соседи не нашлись, значит нужно подняться на 1 уровень вверх
        this->parent->findNeighbour(contact);
    }
    //До этой точки дойду, только если это голова, но это значит, что
    //все квадраты уже проверены, и нужно вернуть nullptr
    if(this->isHead) return nullptr;
}

Contact *Plate::checkQuad(Contact *contact) {
    //cout << "checkQuad():\n";
    if(this->isLeaf){
        //cout << "checkQuad():\tleaf!" << endl;
        for(auto & cont : this->contacts){
            if(cont->getX()!=contact->getX() || cont->getY()!=contact->getY()) return cont;
        }
        return nullptr;
    }
    //cout << "checkQuad():\tNot leaf!" << endl;
    //Часть с рекурсией
    Contact * c;
    c= this->NW->checkQuad(contact);
    if(c!= nullptr) return c;

    c= this->NE->checkQuad(contact);
    if(c!= nullptr) return c;

    c= this->SW->checkQuad(contact);
    if(c!= nullptr) return c;

    c= this->SE->checkQuad(contact);
    if(c!= nullptr) return c;

    //Если ничего не нашел
    return nullptr;
}

double Plate::distance(Contact *c1, Contact *c2) {
    return sqrt( (c1->getX()-c2->getX())^2 + (c1->getY()-c2->getY())^2 );
}

Contact *Plate::searchNearest(Contact * contact, double dist) {
    Contact *c= nullptr;
    if(this->isLeaf){
        for( auto & cont : this->contacts){
            if(Plate::distance(cont, contact)<dist && (cont->getX()!=contact->getX() || cont->getY()!=contact->getY())){
                dist=Plate::distance(cont, contact);
                c=cont;
            }
        }
        return c;
    }
    //Сложно как-то решать неравенство с пересечением квадрата и круга.
    //Я возьму вместо круга с центром P и радиусом R квадрат с центром P и стороной 2R
    double x1, x2, y1, y2;
    x1=contact->getX()-dist; //Границы квадрата
    x2=contact->getX()+dist;
    y1=contact->getY()-dist;
    y2=contact->getY()+dist;
    double x3, x4, y3, y4;
    //хочу проверить, есть пересечение квадранта с заданной областью, и запустить рекурсию, если нужно

    //NW
    x3=max(this->NW->x1, x1);
    x4=min(this->NW->x2, x2);
    y3=max(this->NW->y1, y1);
    y4=min(this->NW->y2, y2);
    if(x3<=x4 && y3<=y4){
        return this->NW->searchNearest(contact, dist);
    }

    //NE
    x3=max(this->NE->x1, x1);
    x4=min(this->NE->x2, x2);
    y3=max(this->NE->y1, y1);
    y4=min(this->NE->y2, y2);
    if(x3<=x4 && y3<=y4){
        return this->NE->searchNearest(contact, dist);
    }

    //SW
    x3=max(this->SW->x1, x1);
    x4=min(this->SW->x2, x2);
    y3=max(this->SW->y1, y1);
    y4=min(this->SW->y2, y2);
    if(x3<=x4 && y3<=y4){
        return this->SW->searchNearest(contact, dist);
    }

    //SE
    x3=max(this->SE->x1, x1);
    x4=min(this->SE->x2, x2);
    y3=max(this->SE->y1, y1);
    y4=min(this->SE->y2, y2);
    if(x3<=x4 && y3<=y4){
        return this->SE->searchNearest(contact, dist);
    }
    return nullptr;
}


