#pragma once

#include <Register.h>
#include <List.hpp>

class Summator {
public:
    using Descr = QList<int>; //Номера регистров для сумматора
    using DescrList = QList<Descr>;//Список номеров регистров для всех сумматоров

    Summator(const QList<const Register*>& = QList<const Register*>());
    Summator(const Summator&);
    Bit GetSum() const;

    Summator& operator=(const Summator &);

private:
    QList<const Register*> _rl;
};
