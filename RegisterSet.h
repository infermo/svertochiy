#pragma once

#include <Register.h>

class RegisterSet {
public:
    RegisterSet(int len);
    RegisterSet(const RegisterSet&);
    ~RegisterSet();

    void PushBit(const Bit &b);

    Register& operator[] (unsigned int);
    int GetLen() const;

private:
    void Shift();

    const int _len;
    Register *_rs;
};
