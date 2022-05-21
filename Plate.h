//
// Created by User on 21.04.2022.
//

#ifndef TASK2_PLATE_H
#define TASK2_PLATE_H

#include "Contact.h"

#define CAPACITY 4
class Plate {
private:
    //Главное предположение - все координаты контактов целые, потому что так сильно проще
    //В целом, это логично, как по мне, ведь размещать контакты на плате нельзя бесконечно близко
    int plateNumber;
    double x1; //Хочу, чтобы можно было создавать плату в прямоугольнике x1-x2-y2-y1-x1
    double y1;
    double x2;
    double y2;
    bool isLeaf; //Хочу, чтобы было удобно проверять, узел это или лист
    bool isHead;
    Plate* NW;   //North West, North East, South West, South East
    Plate* NE;
    Plate* SW;
    Plate* SE;
    Plate* parent;
    vector<Contact*> contacts; //Контакты в квадранте
    Plate * getLeaf(double x, double y); //Возвращает указатель на лист, в котором находится точка [x, y]
    Contact * findNeighbour(Contact *contact); // Возвращает некого соседа, найденного на плате
    Contact * checkQuad(Contact* contact); // Ищет соседей в выделенном квадрате
    static double distance(Contact* c1, Contact *c2); //Расстояние между 2 точками
    Contact * searchNearest(Contact * contact, double dist);

public:
    explicit Plate(double x1=0, double x2=0, double y1=0, double y2=0, int plateNumber=1);
   // ~Plate();
    int addContact(Contact * contact); //Добавляет контакт в квадрант. Вызывает разбиение квадранта, если необходимо
    int subDivide();  //Разбивает квадрант
    Contact * nearestNeighbour(Contact *contact);     //Возвращает указатель на ближайшего соседа к заданному контакту
    vector<Contact *> findContacts(double x1, double x2, double y1, double y2); //Возвращает список контактов в прямоугольнике
    int removeContact(int x, int y); //Убирает контакт с платы в точке [x, y]
    void print();

};


#endif //TASK2_PLATE_H
